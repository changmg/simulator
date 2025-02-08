#include "simulator.h"


using namespace std;


void TestAdder() {
    cout << "--------------------------------------------" << endl;
    cout << "Test 12-bit unsigned adder" << endl;
    // load circuit
    string fileName = "./circuit/rca12.blif";
    NetMan net(fileName); 

    // create simulator based on the circuit
    unsigned randomSeed = 199608224;  // random seed
    int simPattern = 1 << 20;         // # simulation patterns, must be a multiple of 64
    int nFrame = simPattern / 64;  
    Simulator smlt(net, randomSeed, nFrame);

    // simulate
    clock_t st = clock();
    smlt.InpUnifFast(); // generate random input patterns using uniform distribution
    smlt.Sim();         // simulate
    cout << "#nodes = " << net.GetNodeNum() << endl;
    cout << "#input patterns = " << simPattern << endl;
    cout << "simulation runtime = " << clock() - st << "us" << endl;

    // check the result of the 12-bit adder
    bool pass = true;
    for (int i = 0; i < nFrame; ++i) {
        auto add1 = smlt.GetInp(i, 0, 11, false);     // get operand 1 (stored in the first 12 primary inputs) from the i-th pattern, unsigned number
        auto add2 = smlt.GetInp(i, 12, 23, false);    // get operand 2 (stored in the next 12 primary inputs) from the i-th pattern, unsigned number
        auto sum  = smlt.GetOutp(i);                  // get the result from the i-th pattern, unsigned number
        // cout << add1 << "+" << add2 << "=" << sum << endl;
        if (add1 + add2 != sum) {
            pass = false;
            cout << "addition error: " << add1 << "+" << add2 << "=" << sum << endl;
        }
    }
    if (pass)
        cout << "addition test passed" << endl;
    else
        cout << "addition test failed" << endl;
}


void TestMultiplier() {
    cout << "--------------------------------------------" << endl;
    cout << "Test 16-bit signed multiplier" << endl;
    // load circuit
    string fileName = "./circuit/signed-multiplier-16x16.blif";
    NetMan net(fileName); 

    // create simulator based on the circuit
    unsigned randomSeed = 199608224;  // random seed
    int simPattern = 1 << 20;         // # simulation patterns, must be a multiple of 64
    int nFrame = simPattern / 64;  
    Simulator smlt(net, randomSeed, nFrame);

    // simulate
    clock_t st = clock();
    smlt.InpUnifFast(); // generate random input patterns using uniform distribution
    smlt.Sim();         // simulate
    cout << "#nodes = " << net.GetNodeNum() << endl;
    cout << "#input patterns = " << simPattern << endl;
    cout << "simulation runtime = " << clock() - st << "us" << endl;

    // check the result of the 12-bit multiplier
    bool pass = true;
    for (int i = 0; i < nFrame; ++i) {
        auto mul1 = smlt.GetInp(i, 0, 15, true);     // get operand 1 (stored in the first 16 primary inputs) from the i-th pattern, signed number
        auto mul2 = smlt.GetInp(i, 16, 31, true);    // get operand 2 (stored in the next 16 primary inputs) from the i-th pattern, signed number
        auto prod = smlt.GetOutp(i, true);           // get the result from the i-th pattern, signed number
        // cout << mul1 << "*" << mul2 << "=" << prod << endl;
        if (mul1 * mul2 != prod) {
            pass = false;
            cout << "multiplication error: " << mul1 << "*" << mul2 << "=" << prod << endl;
        }
    }
    if (pass)
        cout << "multiplication test passed" << endl;
    else
        cout << "multiplication test failed" << endl;
}


void TestSignalProbability() {
    cout << "--------------------------------------------" << endl;
    cout << "Test signal probability" << endl;
    // load circuit
    string fileName = "./circuit/rca12.blif";
    NetMan net(fileName); 

    // create simulator based on the circuit
    unsigned randomSeed = 199608224;  // random seed
    int simPattern = 1 << 20;         // # simulation patterns, must be a multiple of 64
    int nFrame = simPattern / 64;  
    Simulator smlt(net, randomSeed, nFrame);

    // simulate
    clock_t st = clock();
    smlt.InpUnifFast(); // generate random input patterns using uniform distribution
    smlt.Sim();         // simulate
    cout << "#nodes = " << net.GetNodeNum() << endl;
    cout << "#input patterns = " << simPattern << endl;
    cout << "simulation runtime = " << clock() - st << "us" << endl;

    // print the signal probability of each node
    cout << "**** signal probability ****" << endl;
    for (int i = 0; i < net.GetIdMaxPlus1(); ++i) { // iterate all nodes
        if (!net.IsObj(i)) // skip non-object
            continue;
        double prob = smlt.GetSignalProb(i); // get the signal probability of the i-th node
        cout << "Node: " << setw(10) << net.GetName(i)
             << ",\t Signal Probability: " << setw(6) << prob 
             << ",\t Switching Activity: " << setw(6) << prob * (1 - prob) << endl;
    }
    cout << "********" << endl;
}


int main(int argc, char * argv[]) {
    // start ABC engine
    GlobStartAbc();

    // test 12-bit unsigned adder
    TestAdder();

    // test 16-bit signed multiplier
    TestMultiplier();

    // get signal probability
    TestSignalProbability();

    // stop ABC engine 
    GlobStopAbc();

    return 0;
}
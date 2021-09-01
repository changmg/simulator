#include "headers.h"
#include "cmdline.h"
#include "simulatorPro.h"


using namespace std;
using namespace cmdline;


parser Cmdline_Parser(int argc, char * argv[])
{
    parser option;
    option.add <string> ("input", 'i', "Original Circuit file", false, "circuit/rca12.blif");
    option.parse_check(argc, argv);
    return option;
}


int main(int argc, char * argv[])
{
    // command line parser
    parser option = Cmdline_Parser(argc, argv);
    string input = option.get <string> ("input");

    // initialize
    Abc_Start();
    Abc_Frame_t * pAbc = Abc_FrameGetGlobalFrame();
    ostringstream command("");
    command << "read_blif " << input;
    DASSERT(!Cmd_CommandExecute(pAbc, command.str().c_str()));
    Abc_Ntk_t * pNtk = Abc_NtkDup(Abc_FrameReadNtk(pAbc));

    // verify 12-bit adder (assume input file is rca12.blif)
    int nFrame = 1 << 24;
    Simulator_Pro_t smlt(pNtk, nFrame);
    random_device rd;
    unsigned seed = static_cast <unsigned> (rd());
    smlt.Input(seed);
    clock_t st = clock();
    smlt.Simulate();
    cout << "runtime = " << clock() - st << "us" << endl;
    // for (int i = 0; i < nFrame; ++i) {
    //     uint64_t add1 = static_cast <uint64_t> (smlt.GetInput(0, 11, i));
    //     uint64_t add2 = static_cast <uint64_t> (smlt.GetInput(12, 23, i));
    //     uint64_t sum  = static_cast <uint64_t> (smlt.GetOutput(0, 12, i));
    //     cout << add1 << "+" << add2 << "=" << sum << endl;
    //     DASSERT(add1 + add2 == sum, "addition error");
    // }

    // recycle memory
    Abc_NtkDelete(pNtk);
    Abc_Stop();

    return 0;
}

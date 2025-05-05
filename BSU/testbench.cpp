#include "mc_connections.h"
#include "auto_gen_fields.h"
#include <mc_scverify.h>
#include "BSU.h"
#include <random>

class Top : public sc_module
{
public:
  CCS_DESIGN(BSU) CCS_INIT_S1(BSU1);

  sc_clock clk;
  SC_SIG(bool, rst_bar);

  Connections::Combinational<BSU_In_Type>        CCS_INIT_S1(in1);
  Connections::Combinational<BSU_Out_Type>       CCS_INIT_S1(out1);

  SC_CTOR(Top)
    :   clk("clk", 1, SC_NS, 0.5,0,SC_NS,true) {
    sc_object_tracer<sc_clock> trace_clk(clk);

    BSU1.clk(clk);
    BSU1.rst_bar(rst_bar);
    BSU1.out1(out1);
    BSU1.in1(in1);

    SC_CTHREAD(reset, clk);

    SC_THREAD(stim);
    sensitive << clk.posedge_event();
    async_reset_signal_is(rst_bar, false);

    SC_THREAD(resp);
    sensitive << clk.posedge_event();
    async_reset_signal_is(rst_bar, false);
  }


  void stim() {
    in1.ResetWrite();
    wait();

    std::random_device rd;              // Seed for RNG
    std::mt19937 gen(rd());             // Mersenne Twister engine
    std::uniform_int_distribution<> dis(0, 100);  // Range: 0 to 100 (adjust as needed)

    cout << "Input: " << endl;
    for (int i = 0; i < 3; i++) {
      BSU_In_Type x;
      for (int n = 0; n < N; n=n+1) {
        int a = dis(gen);
        x.data[n] = a;
	cout << a << " ";
      }
      cout << endl;
      in1.Push(x);
    }

    //sc_stop();
    wait();
  }

  void resp() {
    out1.ResetRead();
    wait();

    wait(100);
    cout << "Output: " << endl;
    while (1) {
      for (int i = 0; i < 3; i++) {
        BSU_Out_Type x = out1.Pop();
        for (int n = 0; n < N; n=n+1) {
          cout << x.data[n] << " ";
        }
        cout << " @ " << sc_time_stamp() << endl;
      }
      sc_stop();
    }
  }

  void reset() {
    rst_bar.write(0);
    wait(5);
    rst_bar.write(1);
    wait();
  }
};

int sc_main(int argc, char **argv)
{
  sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
  sc_report_handler::set_actions(SC_ERROR, SC_DISPLAY);
  sc_trace_file *trace_file_ptr = sc_trace_static::setup_trace_file("trace");

  Top top("top");
  trace_hierarchy(&top, trace_file_ptr);
  sc_start();
  /*if (sc_report_handler::get_count(SC_ERROR) > 0) {
    std::cout << "Simulation FAILED" << std::endl;
    return -1;
  }
  std::cout << "Simulation PASSED" << std::endl;*/
  return 0;
}


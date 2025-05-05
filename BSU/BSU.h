#pragma once

#include "mc_connections.h"
#include "auto_gen_fields.h"
#include <ac_int.h>


#define N 32
struct BSU_In_Type
{
  ac_int<32, false> data[N];
  bool finish;

  AUTO_GEN_FIELD_METHODS(BSU_In_Type, (data, finish))
};
struct BSU_Out_Type
{
  ac_int<32, false> data[N];
  bool finish;

  AUTO_GEN_FIELD_METHODS(BSU_Out_Type, (data, finish))
};


#pragma hls_design top
class BSU : public sc_module
{
public:
  sc_in<bool> CCS_INIT_S1(clk);
  sc_in<bool> CCS_INIT_S1(rst_bar);

  Connections::Out<BSU_Out_Type> CCS_INIT_S1(out1);
  Connections::In <BSU_In_Type>  CCS_INIT_S1(in1);

  SC_CTOR(BSU) {
    SC_THREAD(run);
    sensitive << clk.pos();
    async_reset_signal_is(rst_bar, false);
  }

private:

  void run() {
    out1.Reset();
    in1.Reset();
    wait();                                 // WAIT
#pragma hls_pipeline_init_interval 1
#pragma pipeline_stall_mode flush
    while (1) {
      wait();
      // TODO:
      // Change this to bitonic sort hardware: https://en.wikipedia.org/wiki/Bitonic_sorter

      BSU_In_Type t = in1.Pop();
      BSU_Out_Type temp;
      for (int i = 0; i < N; i=i+1) {
        temp.data[N-1-i] = t.data[i];
      }
      temp.finish = true;
      out1.Push(temp);
    }
  }
};

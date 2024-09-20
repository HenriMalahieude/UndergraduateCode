module register_logic( 
  input clk,  
  input enable ,  
  input [4:0] Data ,   
  output reg [4:0]  Q ) ;    
  
//  on  real  FPGA  board  which  has  clk  signal,  we  use  the  following  always 
//statement: 
//  always @(posedge clk )   
//  begin   
//   if ( enable) begin  
//   Q = Data;   
//  end   
//  end   
// endmodule 
 
// for simulation, we force the statement to execute without clk signal: 
always @(*) begin  
    if ( enable) begin  
          Q = Data;   
          end   
end   
 
endmodule 
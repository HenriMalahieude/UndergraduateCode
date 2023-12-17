module and4( 
input wire enable ,  
input wire a,  
input wire b,  
input wire c,  
output wire r  
 ); 
 
//  
 
assign r = enable & a & b & c;  
 
endmodule 
 
 
// structural model 
 
module decoder_st(   
// I/0 ports  
 input  wire enable ,  
 input  wire a ,  
 input  wire b ,  
 input  wire c ,  
 output wire d0,  
 output wire d1,  
 output wire d2,  
 output wire d3,  
 output wire d4,  
 output wire d5,  
 output wire d6,  
 output wire d7  
 
 ); 
// Using the and4 module to set all outputs  
 
and4 c1(enable, ~a, ~b, ~c, d0);  
and4 c2(enable, ~a, ~b, c, d1);
and4 c3(enable, ~a, b, ~c, d2);
and4 c4(enable, ~a, b, c, d3);
and4 c5(enable, a, ~b, ~c, d4);
and4 c6(enable, a, ~b, c, d5);
and4 c7(enable, a, b, ~c, d6);
and4 c8(enable, a, b, c, d7);
 
endmodule 
 
 
// behavioral model 
 
module decoder_bh( 
 
// I/0 ports  
 
 input wire enable ,  
 input wire a ,  
 input wire b ,  
 input wire c ,  
 output reg d0,  
 output reg d1,  
 output reg d2,  
 output reg d3,  
 output reg d4,  
 output reg d5,  
 output reg d6,  
 output reg d7  
 
 ); 
 
// Internal wire  
wire [3:0] bundle ;  
assign bundle = {enable , a, b, c } ;  
 
// Behavioral description  
 
always @(*) begin  
   
  d0 = 1'b0 ;  
  d1 = 1'b0 ;  
  d2 = 1'b0 ; 
  d3 = 1'b0 ;   
  d4 = 1'b0 ;   
  d5 = 1'b0 ;   
  d6 = 1'b0 ;   
  d7 = 1'b0 ;   
 
// Setting the correct output  
 
  case (bundle) 
   
   4'b1000: d0 = 1'b1 ;  
   4'b1001: d1 = 1'b1 ;  
   4'b1010: d2 = 1'b1 ;  
   4'b1011: d3 = 1'b1 ;  
   4'b1100: d4 = 1'b1 ;  
   4'b1101: d5 = 1'b1 ;  
   4'b1110: d6 = 1'b1 ;  
   4'b1111: d7 = 1'b1 ;  
    
   default : begin  
  d0 = 1'b0 ;  
   end  
   
  endcase  
 
end

endmodule 

module decoder_tb; 
 // Inputs
 reg enable; 
 reg a; 
 reg b; 
 reg c; 
 // Outputs 
 wire d0; 
 wire d1; 
 wire d2; 
 wire d3; 
 wire d4; 
 wire d5; 
 wire d6; 
 wire d7; 
 
 // Instantiate the Unit Under Test (UUT) 
 decoder_st uut ( // change to “decoder_bh” for testing your behavioral model 
  .enable(enable),  
  .a(a),  
  .b(b),  
  .c(c),  
  .d0(d0),  
  .d1(d1),  
  .d2(d2),  
  .d3(d3),  
  .d4(d4),  
  .d5(d5),  
  .d6(d6),  
  .d7(d7) 
 ); 
 
 initial begin 
 
          $dumpfile("dump.vcd"); $dumpvars; 
 
	enable = 1; 
	a = 0;  
	b = 0; 
	c = 0; 
	#100; // Wait for 100 ns  
	$display("TC11 ");
	if ( d0 != 1'b1 ) $display  ("Result is wrong"); 
	d();

	a = 0;  
	b = 0; 
	c = 1; 
	#100; 
	$display("TC12 "); 
	if ( d1 != 1'b1 ) $display  ("Result is wrong");
	d();

	a = 0;  
	b = 1; 
	c = 0; 
	#100; 
	$display("TC13 "); 
	if ( d2 != 1'b1 ) $display  ("Result is wrong"); 
	d();

	a = 0;  
	b = 1; 
	c = 1; 
	#100;     
	$display("TC14 "); 
	if ( d3 != 1'b1 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 0; 
	c = 0; 
	#100;     
	$display("TC15 "); 
	if ( d4 != 1'b1 ) $display  ("Result is wrong");
	d();

	a = 1;  
	b = 0; 
	c = 1; 
	#100;     
	$display("TC16 "); 
	if ( d5 != 1'b1 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 1;
	c = 0; 
	#100;     
	$display("TC17 "); 
	if ( d6 != 1'b1 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 1; 
	c = 1; 
	#100;     
	$display("TC18 "); 
	if ( d7 != 1'b1 ) $display  ("Result is wrong"); 
	d();
 
    // Your test cases ******************* 
	enable = 0;
	a = 0;  
	b = 0; 
	c = 0; 
	#100; // Wait for 100 ns  
	$display("TC21 ");
	if ( d0 != 1'b0 ) $display  ("Result is wrong");
	d();

	a = 0;  
	b = 0; 
	c = 1; 
	#100; 
	$display("TC22 "); 
	if ( d1 != 1'b0 ) $display  ("Result is wrong"); 
	d();

	a = 0;  
	b = 1; 
	c = 0; 
	#100; 
	$display("TC23 "); 
	if ( d2 != 1'b0 ) $display  ("Result is wrong"); 
	d();

	a = 0;  
	b = 1; 
	c = 1; 
	#100;     
	$display("TC24 "); 
	if ( d3 != 1'b0 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 0; 
	c = 0; 
	#100;     
	$display("TC25 "); 
	if ( d4 != 1'b0 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 0; 
	c = 1; 
	#100;     
	$display("TC26 "); 
	if ( d5 != 1'b0 ) $display  ("Result is wrong");
	d();

	a = 1;  
	b = 1;
	c = 0; 
	#100;     
	$display("TC27 "); 
	if ( d6 != 1'b0 ) $display  ("Result is wrong"); 
	d();

	a = 1;  
	b = 1; 
	c = 1; 
	#100;
	$display("TC28 "); 
	if ( d7 != 1'b0 ) $display  ("Result is wrong"); 
	d();
end

task d();
begin
	$display("E:%b, A:%b, B:%b, C:%b", enable, a, b, c);
	$display("%b%b%b%b%b%b%b%b", d0, d1, d2, d3, d4, d5, d6, d7);
end
endtask
endmodule 
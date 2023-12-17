module and3( 
input wire a,  
input wire b,  
input wire c,  
output wire r  
 ); 
 
assign r = a & b & c ;  
 
endmodule 
 
 
// structural model 
 
module mux_st( 
 
// Ports I/O  
input wire s1,  
input wire s0,  
input wire i0,  
input wire i1,  
input wire i2,  
input wire i3,  
output wire d  
); 
 
wire  r1, r2, r3, r4 ;  
 
and3 c1 ( ~s1,~s0,  i0,  r1 ) ; 
and3 c2 ( ~s1, s0,  i1,  r2 ) ; 
and3 c3 ( s1, ~s0,  i2,  r3 ) ; 
and3 c4 ( s1, s0,  i3,  r4 ) ; 
 
assign d = r1 | r2 | r3 | r4 ;  
 
endmodule 
 
 
// behavioral model 
 
module mux_bh( 
 
// Ports I/O  
 
input wire s1,  
input wire s0,  
input wire i0,  
input wire i1,  
input wire i2,  
input wire i3,  
output reg d  
) ;  
 
always @(*) begin  
  
 d = 1'b0 ;  
 
 case ( {s1,s0} )   
  
  2'b00 : d = i0 ;   
  2'b01 : d = i1 ;
  2'b10 : d = i2 ;
  2'b11 : d = i3 ;

 endcase  
 
end  
 
endmodule 

module mux_tb; 
 
 // Inputs 
 reg s1; 
 reg s0; 
 reg i0; 
 reg i1; 
 reg i2; 
 reg i3; 
 
 // Outputs 
 wire d; 
 
 // Instantiate the Unit Under Test (UUT) 
 mux_bh uut ( // change to “mux_st” for testing your structural  
  .s1(s1),  
  .s0(s0),  
  .i0(i0),  
  .i1(i1),  
  .i2(i2),  
  .i3(i3),  
  .d(d) 
 ); 
 
 initial begin 
 
	$dumpfile("dump.vcd"); $dumpvars; 
 
  i0 = 1; 
  i1 = 0; 
  i2 = 1; 
  i3 = 0; 
 
  s1 = 0; 
  s0 = 0; 
  #100; 
  $display("TC11 "); 
  if ( d != i0 ) $display  ("Result is wrong");
  o();

  s1 = 0; 
  s0 = 1; 
  #100; 
  $display("TC12 "); 
  if ( d != i1 ) $display  ("Result is wrong");
  o();
 
  s1 = 1; 
  s0 = 0; 
  #100; 
  $display("TC13 "); 
  if ( d != i2 ) $display  ("Result is wrong");
  o();
 
  s1 = 1; 
  s0 = 1; 
  #100; 
  $display("TC14 "); 
  if ( d != i3 ) $display  ("Result is wrong"); 
  o();
 
							  // Your test cases

	 i0 = 0; 
  i1 = 1; 
  i2 = 0; 
  i3 = 1; 
 
  s1 = 0; 
  s0 = 0; 
  #100; 
  $display("TC21 "); 
  if ( d != i0 ) $display  ("Result is wrong");
  o();

  s1 = 0; 
  s0 = 1; 
  #100; 
  $display("TC22 "); 
  if ( d != i1 ) $display  ("Result is wrong");
  o();
 
  s1 = 1; 
  s0 = 0; 
  #100; 
  $display("TC23 "); 
  if ( d != i2 ) $display  ("Result is wrong");
  o();
 
  s1 = 1; 
  s0 = 1; 
  #100; 
  $display("TC24 "); 
  if ( d != i3 ) $display  ("Result is wrong"); 
  o();
			
 end

task o();
	begin
		$display("i:%b%b%b%b", i0, i1, i2, i3);
		$display("s:%b%b", s1, s0);
		$display("out:%b", d);
	end
endtask
		 
endmodule 
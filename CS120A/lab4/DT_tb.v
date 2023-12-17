// Code your testbench here
// or browse Examples
`timescale 1ns/1ps
module display_tb_tb;
	reg clk = 0;

	reg sw0; // Switch input  
	reg sw1; // Switch input  
	reg sw2; // Switch input  
	reg sw3; // Switch  input  

	wire [3:0] anode;  // LED selector   
	wire [7:0] segments;  // Segment signals

	dispmux_main_bh item(clk, sw0, sw1, sw2, sw3, anode, segments);
	initial begin
		$dumpfile("dump_dtbtb.vcd"); $dumpvars;

		sw0 = 0; sw1 = 0; sw2 = 0; sw3 = 0;
		$display("TC0 ");
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);

		sw0 = 0; sw1 = 0; sw2 = 1; sw3 = 0;
		$display("\nTC1 ");
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);

		sw0 = 0; sw1 = 1; sw2 = 0; sw3 = 0;
		$display("\nTC2 ");
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
		clk = 1; #5; clk = 0; #5
		$display("%b selects %b", anode, segments);
	end
endmodule
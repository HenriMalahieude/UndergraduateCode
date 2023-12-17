`include "edgedetector.v"

module testbench;
	reg clk = 0;
	reg sig;
	wire out;

	edgedetector_bh ed(clk, sig, out);

	initial begin

		sig = 0;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC0\n Signal: %b, Out: %b", sig, out);

		sig = 0;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC1\n Signal: %b, Out: %b", sig, out);

		sig = 1;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC2\n Signal: %b, Out: %b", sig, out);

		sig = 0;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC3\n Signal: %b, Out: %b", sig, out);

		sig = 1;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC4\n Signal: %b, Out: %b", sig, out);

		sig = 1;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC5\n Signal: %b, Out: %b", sig, out);

	end
endmodule
`include "flightattendat.v"

module testbench;
	reg clk = 0;
	reg call, cancel;
	wire lightOn;

	fasystem_bh fa(clk, call, cancel, lightOn);
	initial begin

		call = 0; cancel = 0;
		clk = 0; #5; clk = 1; #5; clk = 0; #5;
		$display("TC0\n Call: %b, Cancel: %b, Light: %b", call, cancel, lightOn);

		call = 0; cancel = 1;
		clk = 1; #5; clk = 0; #5;
		$display("TC1\n Call: %b, Cancel: %b, Light: %b", call, cancel, lightOn);

		call = 1; cancel = 0;
		clk = 1; #5; clk = 0; #5;
		$display("TC2\n Call: %b, Cancel: %b, Light: %b", call, cancel, lightOn);

		call = 0; cancel = 1;
		clk = 1; #5; clk = 0; #5;
		$display("TC3\n Call: %b, Cancel: %b, Light: %b", call, cancel, lightOn);

		call = 1; cancel = 1;
		clk = 1; #5; clk = 0; #5;
		$display("TC0\n Call: %b, Cancel: %b, Light: %b", call, cancel, lightOn);
	end


endmodule
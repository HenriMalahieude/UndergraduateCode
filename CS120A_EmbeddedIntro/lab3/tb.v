`timescale 1ns / 1ps
// http://www.electronics-tutorials.ws/combination/comb_6.html
module bcdtoled_tb;
	// Inputs
	reg sw0;
	reg sw1;
	reg sw2;
	reg sw3;
	// Outputs
	wire a;
	wire b;
	wire c;
	wire d;
	wire e;
	wire f;
	wire g;
	// Instantiate the Unit Under Test (UUT)
	// bcdto7led_st uut (
	bcd_to_7led_bh uut (
		.sw0(sw0),
		.sw1(sw1),
		.sw2(sw2),
		.sw3(sw3),
		.a(a),
		.b(b),
		.c(c),
		.d(d),
		.e(e),
		.f(f),
		.g(g)
);

	initial begin
		$dumpfile("dump.vcd"); $dumpvars;
		// Zero
		sw3 = 0; sw2 = 0; sw1 = 0; sw0 = 0;
		#100;
		$display("TC0 ");
		if ( {a,b,c,d,e,f,g} != 7'b0000001 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//One
		sw3 = 0; sw2 = 0; sw1 = 0; sw0 = 1;
		#100;
		$display("TC1 ");
		if ( {a,b,c,d,e,f,g} != 7'b1001111 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Two
		sw3 = 0; sw2 = 0; sw1 = 1; sw0 = 0;
		#100;
		$display("TC2 ");
		if ( {a,b,c,d,e,f,g} != 7'b0010010 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Three
		sw3 = 0; sw2 = 0; sw1 = 1; sw0 = 1;
		#100;
		$display("TC3 ");
		if ( {a,b,c,d,e,f,g} != 7'b0000110 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Four
		sw3 = 0; sw2 = 1; sw1 = 0; sw0 = 0;
		#100;
		$display("TC4 ");
		if ( {a,b,c,d,e,f,g} != 7'b1001100 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Five
		sw3 = 0; sw2 = 1; sw1 = 0; sw0 = 1;
		#100;
		$display("TC5 ");
		if ( {a,b,c,d,e,f,g} != 7'b0100100 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Six
		sw3 = 0; sw2 = 1; sw1 = 1; sw0 = 0;
		#100;
		$display("TC6 ");
		if ( {a,b,c,d,e,f,g} != 7'b0100000 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Seven
		sw3 = 0; sw2 = 1; sw1 = 1; sw0 = 1;
		#100;
		$display("TC7 ");
		if ( {a,b,c,d,e,f,g} != 7'b0001111 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
		
		//Eight
		sw3 = 1; sw2 = 0; sw1 = 0; sw0 = 0;
		#100;
		$display("TC8 ");
		if ( {a,b,c,d,e,f,g} != 7'b0000000 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});

		//Nine
		sw3 = 1; sw2 = 0; sw1 = 0; sw0 = 1;
		#100;
		$display("TC9 ");
		if ( {a,b,c,d,e,f,g} != 7'b0001100 ) $display ("Result is wrong %b", {a,b,c,d,e,f,g});
	end
endmodule

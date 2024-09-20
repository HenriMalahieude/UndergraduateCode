module edgedetector_bh(
	input  wire clk,
	input  wire signal,
	output reg outedge
	);

	wire slow_clk ;

	reg [1:0] c_state ;
	reg [1:0] r_state ;

	// Define your FSM states
	localparam ZERO = 'd0;
	localparam CHANGE = 'd1;
	localparam ONE = 'd2;

	// EECS150 - Digital Design Lecture 17 - Finite State Machines Revisited

	// Code for clkdiv module is given below. Create a new Verilog module in the
	//same project with the given code

	// Comb. logic.

	always @(*) begin

	case (r_state)

		ZERO : begin
			c_state =  signal == 1'b1 ? CHANGE :  ZERO ;
			outedge = 1'd0 ;
		end

		CHANGE : begin
			c_state = ONE;
			outedge = 1'd1;
		end

		ONE : begin
			c_state = signal == 1'b1 ? ONE : ZERO;
			outedge = 1'd0;
		end

		default : begin
			c_state = ZERO ;
			outedge = 1'd0 ;
		end

	endcase

	end

	// Seq. logic
	always @( posedge clk ) begin
		r_state <= c_state ;
	end

endmodule
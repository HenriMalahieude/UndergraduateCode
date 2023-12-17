`timescale 1ns / 1ps
module bcd_to_7led_bh (
		input wire sw0 , // Switches 
		input wire sw1 ,
		input wire sw2 ,
		input wire sw3 ,
		output reg a , // LED segments
		output reg b ,
		output reg c ,
		output reg d ,
		output reg e ,
		output reg f ,
		output reg g
		);
	// Internal wire
	wire [3:0] bundle ;
	assign bundle = {sw3,sw2,sw1,sw0 } ;

	wire [7:0] outBundle;
	assign outBundle = {a,b,c,d,e,f,g};

	always @(*) begin
		// Setting the segments signals (Initialize all to off/1)
		a = 1'b1 ;
		b = 1'b1 ;
		c = 1'b1 ;
		d = 1'b1 ;
		e = 1'b1 ;
		f = 1'b1 ;
		g = 1'b1 ;

		case ( bundle )
			4'b0000 : begin // 0
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b0 ;
				e = 1'b0 ;
				f = 1'b0 ;
				g = 1'b1 ; 
			end
			4'b0001 : begin 
				a = 1'b1 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b1 ;
				e = 1'b1 ;
				f = 1'b1 ;
				g = 1'b1 ; 
			end
			4'b0010 : begin 
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b1 ;
				d = 1'b0 ;
				e = 1'b0 ;
				f = 1'b1 ;
				g = 1'b0 ; 
			end
			4'b0011 : begin 
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b0 ;
				e = 1'b1 ;
				f = 1'b1 ;
				g = 1'b0 ; 
			end
			4'b0100 : begin 
				a = 1'b1 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b1 ;
				e = 1'b1 ;
				f = 1'b0 ;
				g = 1'b0 ; 
			end
			4'b0101 : begin 
				a = 1'b0 ;
				b = 1'b1 ;
				c = 1'b0 ;
				d = 1'b0 ;
				e = 1'b1 ;
				f = 1'b0 ;
				g = 1'b0 ; 
			end
			4'b0110 : begin 
				a = 1'b0 ;
				b = 1'b1 ;
				c = 1'b0 ;
				d = 1'b0 ;
				e = 1'b0 ;
				f = 1'b0 ;
				g = 1'b0 ; 
			end
			4'b0111 : begin 
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b1 ;
				e = 1'b1 ;
				f = 1'b1 ;
				g = 1'b1 ; 
			end
			4'b1000 : begin 
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b0 ;
				e = 1'b0 ;
				f = 1'b0 ;
				g = 1'b0 ; 
			end
			4'b1001 : begin 
				a = 1'b0 ;
				b = 1'b0 ;
				c = 1'b0 ;
				d = 1'b1 ;
				e = 1'b1 ;
				f = 1'b0 ;
				g = 1'b0 ; 
			end
			// Your code goes here for the other 8 numbers (1-9)
		endcase
	end
endmodule
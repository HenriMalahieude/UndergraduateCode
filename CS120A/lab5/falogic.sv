module falogic( 
 output r,  // We label our output as r instead of z 
 input x,  
 input y,  
 input cin  
    ); 
wire t1; 
xor cx1 ( t1, x,y  );  
xor cx2 ( r, t1, cin  );  
 
endmodule 
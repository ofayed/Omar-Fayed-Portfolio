`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/27/2022 11:33:55 AM
// Design Name: 
// Module Name: alucontrol
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module alucontrol(

input [2:0]inst1,
input inst2,
input inst25,
output reg [3:0] alusel,
input  [1:0] aluop
    );
     /*        4'b00_00 : r = add;
            4'b00_01 : r = add;
            4'b00_11 : r = b;
            // logic
            4'b01_00:  r = a | b;
            4'b01_01:  r = a & b;
            4'b01_11:  r = a ^ b;
            // shift
            4'b10_00:  r=sh; //sll
            4'b10_01:  r=sh; //srl
            4'b10_10:  r=sh; //sra
            // slt & sltu
            4'b11_01:  r = {31'b0,(sf != vf)}; 
            4'b11_11:  r = {31'b0,(~cf)};   
          */  
 always @(*)
 begin
case (aluop)
 2'b00:alusel = 4'b00_00; //add
 2'b01:alusel = 4'b00_01; //sub
 2'b10:begin
     if(inst1 == 3'b110) alusel = 4'b01_00; //or
     else if(inst1 == 3'b111) alusel = 4'b01_01; //and
     else if (inst1 == 3'b000 && inst2 == 0 && inst25 == 0) alusel = 4'b00_00; //add
     else if (inst1 == 3'b000 && inst2 == 1 && inst25 == 0) alusel = 4'b00_01; //sub
     else if (inst1 == 3'b000 && inst2 == 0 && inst25 == 1) alusel = 4'b10_11; //mul
     else if (inst1 == 3'b100 && inst2 == 0 && inst25 == 1) alusel = 4'b11_10; //div
     else if (inst1 == 3'b110 && inst2 == 0 && inst25 == 1) alusel = 4'b00_10; //rem
     else if (inst1 == 3'b001) alusel = 4'b10_00; //sll 
     else if (inst1 == 3'b010) alusel = 4'b11_01; //slt
     else if (inst1 == 3'b011) alusel = 4'b11_11; //sltu
     else if (inst1 == 3'b100) alusel = 4'b01_11; //xor
     else if (inst1 == 3'b101 && inst2 == 0) alusel = 4'b10_01; //srl
     else if (inst1 == 3'b101 && inst2 == 1) alusel = 4'b10_10; //sra
  end
  2'b11: begin
      if(inst1 == 3'b000) alusel = 4'b00_00; //addi
      else if(inst1 == 3'b010) alusel = 4'b11_01; //slti
      else if(inst1 == 3'b011) alusel = 4'b11_11; //sltiu
      else if(inst1 == 3'b100) alusel = 4'b01_11; // xori
      else if(inst1 == 3'b110) alusel = 4'b01_00; //ori
      else if(inst1 == 3'b111) alusel = 4'b01_01; // andi
      else if(inst1 == 3'b001) alusel = 4'b10_00; //slli
      else if(inst1 == 3'b101 && inst2 == 0) alusel = 4'b10_01; //srli
      else if(inst1 == 3'b101 && inst2 == 1) alusel = 4'b10_10; //srai
  end
 default: alusel= 4'b00_11;
 endcase
 end
 


endmodule
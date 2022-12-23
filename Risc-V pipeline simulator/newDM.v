`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/04/2022 09:05:19 AM
// Design Name: 
// Module Name: dataMEM
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


module newDM (
input clk, input MemRead, input MemWrite,
  input [31:0] addr, input [31:0] data_in, input [2:0] inst1, output reg [31:0] data_out);
  reg [7:0] mem [0:511];

//wire [7:0] i,k,o,f;
//assign i = addr ;
//assign k = addr + 1;
//assign o = addr + 2;
//assign f = addr + 3;

//10001
initial begin
  
  {mem[386],mem[385],mem[384],mem[383]} = 32'd17;
  {mem[390],mem[389],mem[388], mem[387]} = 32'd9;
  {mem[394], mem[393], mem[392], mem[391]}= 32'd25;
  
   
    {mem[3],mem[2],mem[1],mem[0]} = 32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0 
 //added to be skipped since PC starts with 4 after reset
  {mem[7],mem[6],mem[5], mem[4]} = 32'h0x17f02083 ; //lw x1, 383(x0) - 17
  {mem[11], mem[10], mem[9], mem[8]}=32'h0x18302103 ; //lw x2, 387(x0) - 9
  {mem[15], mem[14], mem[13], mem[12]}=32'h0x18702183 ; //lw x3, 391(x0)  - 25
  {mem[19], mem[18], mem[17], mem[16]}=32'b0000000_00010_00001_110_00100_0110011 ; //or x4, x1, x2 - 25
  {mem[23], mem[22], mem[21], mem[20]}=32'h0x00320463; //beq x4, x3, 8
  {mem[27], mem[26], mem[25], mem[24]}=32'b0000000_00010_00001_000_00011_0110011 ; //add x3, x1, x2
  {mem[31], mem[30], mem[29], mem[28]}=32'b0000000_00010_00011_000_00101_0110011 ; //add x5, x3, x2 - branch jumps here: 34
  {mem[35], mem[34], mem[33], mem[32]}=32'h0x185025a3; //sw x5, 907(x0) - 34
  {mem[39], mem[38], mem[37], mem[36]}=32'h0x0012f333; //and x6 x5 x1 - 0
  {mem[43], mem[42], mem[41], mem[40]}=32'h0x402083b3; //sub x7 x1 x2 - 8 
  {mem[47], mem[46], mem[45], mem[44]}=32'h0x00708433; //add x8 x1 x7 - 25
  {mem[51], mem[50], mem[49], mem[48]}=32'h0x002404b3; //add x9 x8 x2 - 34
  
////  //Test For Forwarding & Control (Branch) Hazards
//    {mem[3],mem[2],mem[1],mem[0]} = 32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0 
// //added to be skipped since PC starts with 4 after reset
//  {mem[7],mem[6],mem[5], mem[4]} = 32'h0x17f02083 ; //lw x1, 383(x0) - 17
//  {mem[11], mem[10], mem[9], mem[8]}=32'h0x18302103 ; //lw x2, 387(x0) - 9
//  {mem[15], mem[14], mem[13], mem[12]}=32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0
//  {mem[19], mem[18], mem[17], mem[16]}=32'h0x18702183 ; //lw x3, 391(x0)  - 25
//  {mem[23], mem[22], mem[21], mem[20]}=32'b0000000_00010_00001_110_00100_0110011 ; //or x4, x1, x2 - 25
//  {mem[27], mem[26], mem[25], mem[24]}=32'h0x00320463; //beq x4, x3, 8
//  {mem[31], mem[30], mem[29], mem[28]}=32'b0000000_00010_00001_000_00011_0110011 ; //add x3, x1, x2
//  {mem[35], mem[34], mem[33], mem[32]}=32'b0000000_00010_00011_000_00101_0110011 ; //add x5, x3, x2 - branch jumps here: 34
//  {mem[39], mem[38], mem[37], mem[36]}=32'h0x185025a3; //sw x5, 907(x0) - 34
//  {mem[43], mem[42], mem[41], mem[40]}=32'h0x0012f333; //and x6 x5 x1 - 0
//  {mem[47], mem[46], mem[45], mem[44]}=32'h0x402083b3; //sub x7 x1 x2 - 8 
//  {mem[51], mem[50], mem[49], mem[48]}=32'h0x00708433; //add x8 x1 x7 - 25
//  {mem[55], mem[54], mem[53], mem[52]}=32'h0x002404b3; //add x9 x8 x2 - 34
//  {mem[59], mem[58], mem[57], mem[56]}=32'h0x02208533; //mul x10 x1 x2 - 153
//  {mem[63], mem[62], mem[61], mem[60]}=32'h0x021545b3; //div x11 x10 x1 - 9
  
  //Test For Forwarding Only
  /* 
  {mem[3],mem[2],mem[1],mem[0]} = 32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0 
 //added to be skipped since PC starts with 4 after reset
  {mem[7],mem[6],mem[5], mem[4]} = 32'h0x37f02083 ; //lw x1, 895(x0) - 17
  {mem[11], mem[10], mem[9], mem[8]}=32'h0x38302103 ; //lw x2, 899(x0) - 9
  {mem[15], mem[14], mem[13], mem[12]}=32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0
  {mem[19], mem[18], mem[17], mem[16]}=32'h0x38702183 ; //lw x3, 903(x0)  - 25
  {mem[23], mem[22], mem[21], mem[20]}=32'b0000000_00010_00001_110_00100_0110011 ; //or x4, x1, x2 - 25
  {mem[27], mem[26], mem[25], mem[24]}=32'h0x00320a63; //beq x4, x3, 20
  {mem[31], mem[30], mem[29], mem[28]}=32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0
  {mem[35], mem[34], mem[33], mem[32]}=32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0
  {mem[39], mem[38], mem[37], mem[36]}=32'b0000000_00000_00000_000_00000_0110011 ; //add x0, x0, x0
  {mem[43], mem[42], mem[41], mem[40]}=32'b0000000_00010_00001_000_00011_0110011 ; //add x3, x1, x2
  {mem[47], mem[46], mem[45], mem[44]}=32'b0000000_00010_00011_000_00101_0110011 ; //add x5, x3, x2 - branch jumps here: 34
  {mem[51], mem[50], mem[49], mem[48]}=32'h0x385025a3; //sw x5, 907(x0) - 34
  {mem[55], mem[54], mem[53], mem[52]}=32'h0x0012f333; //and x6 x5 x1 - 0
  {mem[59], mem[58], mem[57], mem[56]}=32'h0x402083b3; //sub x7 x1 x2 - 8 
  {mem[63], mem[62], mem[61], mem[60]}=32'h0x00708433; //add x8 x1 x7 - 25
  {mem[67], mem[66], mem[65], mem[64]}=32'h0x002404b3; //add x9 x8 x2 - 34
*/
 end
 

//pc will enter in posedge of the clk and fetch the code 
 always @(posedge clk)
begin
	 data_out <= {mem[addr+3], mem[addr+2], mem[addr+1], mem[addr]};
end
  
 //address will come at the negedve of the clk to store value when needed
always @(negedge clk)
begin
	if(MemWrite == 1)
      begin
        if(inst1 == 3'b000) mem[addr] <= data_in[7:0]; //SB
        else if(inst1 == 3'b001) {mem[addr+1], mem[addr]} <= data_in[15:0]; //SH
        else if(inst1 == 3'b010) {mem[addr+3], mem[addr+2], mem[addr+1], mem[addr]} <= data_in[31:0]; //SW
      end
end

always @(*)
begin
	if(MemRead == 1)
	begin 
      if(inst1 == 3'b000)  data_out <= {{24{mem[addr][7]}}, mem[addr]}; //LB
      else if(inst1 == 3'b001) data_out <= {{16{mem[addr+1][7]}},mem[addr+1], mem[addr]}; //LH
      else if(inst1 == 3'b010) data_out <= {mem[addr+3], mem[addr+2], mem[addr+1], mem[addr]}; //LW
      else if(inst1 == 3'b100)  data_out <= {24'b0, mem[addr]}; //LBU
      else if(inst1 == 3'b101)  data_out <= {16'b0, mem[addr+1], mem[addr]}; //LHU
	end
end

endmodule

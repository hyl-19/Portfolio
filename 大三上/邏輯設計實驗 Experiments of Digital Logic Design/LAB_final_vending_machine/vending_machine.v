module vending_machine(
  input clk, 
  input reset,
  input[31:0] howManyTicket,
  input[2:0] origin,
  input[2:0] destination,
  input[31:0] money,
  output reg[31:0] costOfTicket,
  output reg[31:0] moneyToPay,
  output reg[31:0] totalMoney
);

parameter state_0 = 2'd0;
parameter state_1 = 2'd1;
parameter state_2 = 2'd2;
parameter state_3 = 2'd3;

reg[31:0] r1, t1, p1;

reg[1:0] state, next_state;
reg[31:0] diff; // the origin to destination

always @(posedge clk or reset) begin
  if ( reset ) begin
    state <= state_3;
    
  end
  else state <= next_state;
end

always @( posedge clk ) begin
  case(state) 
    state_0:begin  
            $display("origin and dest : %d and %d", origin, destination);
            diff = 32'd0;
            diff = origin - destination;
            costOfTicket = (diff[2]) ? (-diff+1) * 5 : (diff+1) * 5;  
            $display("how much a ticket : %d", costOfTicket);
    end
    state_1:begin 
            $display("how many ticket : %d", howManyTicket);
            moneyToPay = costOfTicket * howManyTicket;
            p1 = moneyToPay ;
            $display("how much : %d", moneyToPay);
    end
    state_2:begin
            $display("input money : %d", money);
            totalMoney = totalMoney + money;
            t1= totalMoney ;
            moneyToPay = moneyToPay - money;
            r1 = moneyToPay ;
    end
    state_3:begin
            if ( r1 <= 0 || totalMoney > p1 ) begin
              $display("return %d dollar and %d tickets", t1-p1, howManyTicket);
              totalMoney = 32'd0;
              moneyToPay = 32'd0;
             	costOfTicket = 32'd0;
      	     end
            else if ( p1 > 0) begin
              $display("return %d dollar and 0 tickets", t1);
              totalMoney = 32'd0;
              	moneyToPay = 32'd0;
            costOfTicket = 32'd0;
            end
            else begin
              totalMoney = 32'd0;
              moneyToPay = 32'd0;
              costOfTicket = 32'd0;
            end
            end
  endcase

end

always @(state or posedge clk) begin
  case(state)
    state_0: next_state = state_1;
    state_1: if ( reset ) next_state = state_3 ;
  	          else next_state = state_2; // cancel
    state_2: if ( moneyToPay > 0 ) next_state = state_2;
             else if ( moneyToPay <= 0) next_state = state_3;
    state_3: next_state = state_0;
  endcase
end

endmodule
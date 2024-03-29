library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Chenillard is

	port(
	
		clk : in std_logic := '0';
		reset_n : in std_logic :='0';
		leds : out std_logic_vector(7 downto 0);
		button : in std_logic :='0'		 
		 );
		
end entity Chenillard;

architecture arch of Chenillard is


    component Chenillard_sys is
        port (
            clk_clk                           : in  std_logic                    := 'X'; -- clk
            leds_external_connection_export   : out std_logic_vector(7 downto 0);        -- export
            reset_reset_n                     : in  std_logic                    := 'X'; -- reset_n
            button_external_connection_export : in  std_logic                    := 'X'  -- export
        );
    end component Chenillard_sys;
	 
begin

    u0 : component Chenillard_sys
        port map (
            clk_clk                           => clk,     -- clk.clk
            leds_external_connection_export   => leds,    -- leds_external_connection.export
            reset_reset_n                     => reset_n, -- reset.reset_n
            button_external_connection_export => button   -- button_external_connection.export
        );


end arch;
%% @author John L. Singleton <jsinglet@gmail.com>

%% @doc Provides main functions for garage door manipulations.

-module(garage).
%%-compile(export_all).
-export([start/0]).


%% Used for communication with Teensy pin colors
-define(RED, "R").
-define(BLUE, "B").
-define(GREEN, "G").
-define(OPEN_DOOR, "1").

-define(BLINKS_GRANT, 9).
-define(BLINKS_DENY, 2).
-define(BLINKS_THINK, 1).

-define(LOCKOUT, 20).

%% starts the garage door opener process
start() ->
    spawn(fun() -> loop(0) end).
		  
%%
%% Receive loop
%%

loop(LastOpen)  ->
    receive
	{thinking, Teensy}       -> blink(Teensy, thinking),
				   loop(LastOpen);
	{access_denied, Teensy}  -> blink(Teensy, access_denied),
				   loop(LastOpen);
	{access_granted, Teensy} -> {_,S,_} = now(),
				    if  
					(S - LastOpen) >= ?LOCKOUT ->
					    toggleDoor(Teensy),
					    blink(Teensy, access_granted),
					    loop(S);
						
					true -> io:format("[garage] Was going to open, but not enough time has passed.~n", []),
						loop(LastOpen)
				    end;

	%% don't fail if we get weird messages
	Any ->
	    io:format("[garage] Got Invalid Message: ~p~n", [Any]),
	    loop(LastOpen)
    end.



%%
%% Support functions
%%


%% opens the door to the garage
toggleDoor (Teensy)            ->
    io:format("[garage] OPENING DOOR~n"),
    utils:unlock(Teensy).
	

%% set of guards that blink the light according to status. 
blink (Teensy, access_denied)  ->
    io:format("[garage] ACCESS DENIED ~n"),
    utils:blink(Teensy, ?RED, ?BLINKS_DENY);
blink (Teensy, thinking)       -> 
    io:format("[garage] THINKING ~n"),
    utils:blink(Teensy, ?BLUE, ?BLINKS_THINK);
blink (Teensy, access_granted) -> 
    io:format("[garage] ACCESS GRANTED ~n"),
    utils:blink(Teensy, ?GREEN, ?BLINKS_GRANT).

    
    

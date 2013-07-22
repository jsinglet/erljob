%% @author John L. Singleton <jsinglet@gmail.com>

%% @doc Main listener. Reads from the audio interface and dispatches messages
%% to the garage door opener processes.

-module(big_brother).
%%-compile(export_all).
-export([start/1]).

%% starts big brother listener.
start(Config) ->

    %% The main loop that does the listening -- there should only really be one of these.
    Listener = fun() ->
    %% register the single instance of the garage opener. if this dies, this entire process will
    %% restart
		       register(gate_keeper, garage:start()),
		       loop({0, Config}) end,


    utils:keep_alive(big_brother, Listener).
    

%%
%% Receive loop
%%


%% reads from the audio device continuously 
loop({Iteration, Config}) ->
    {config, {teensy, Teensy}, {mic, Mic}, _, _, _} = Config,
    
    io:format("[big_brother ~p] Reading one second of audio from ~p ~n", [Iteration, Mic]),

    %% blink once for thinking
    gate_keeper ! {thinking, Teensy},

    %% read audio
    Sample = utils:tmpfile(),

    Record = utils:record_cmd(Sample, Mic),
    
    os:cmd(Record),
    

    %Sample = "/tmp/test.raw",

    %% determine if match -- this runs outside of this thread
    spawn(fun() -> utils:authenticate(Sample, Config), file:delete(Sample)  end),
    %spawn(fun() -> utils:authenticate(Sample, Config)  end),
    
    %timer:sleep(1000),
    
    loop({Iteration+1, Config}).
    

%% @author John L. Singleton <jsinglet@gmail.com>

%% @doc Various utility functions

-module(utils).
%%-compile(export_all).
-export([authenticate/2, keep_alive/2, tmpfile/0, record_cmd/2, on_exit/2, unlock/1,blink/3,flatten_keys/2]).

-on_load(init/0).


%% Process MGMT functions

keep_alive(Name, Fun) ->
    register(Name, Pid = spawn(Fun)),
    on_exit(Pid, fun(_Why) -> keep_alive(Name, Fun) end).

on_exit(Pid, Fun) ->
    spawn(fun() ->
	process_flag(trap_exit, true),
		  link(Pid),
		  receive
		      {'EXIT', Pid, Why} ->
			  
			  Fun(Why)
		  end
		end).
    
%% File and command helpers.

tmpfile() ->
    {A,B,C}=now(),
    lists:flatten(io_lib:format("/tmp/~p.~p.~p",[A,B,C])).


record_cmd(Tmp,Device) ->
    lists:flatten(io_lib:format("/usr/bin/arecord -f S16_LE -t raw -r 44100 -c 1 -d 1 -D ~p ~p",[Device, Tmp])).


    
%% Actual authentication code
 
authenticate(Sample, Config) ->
    %% extract some parameters
    {config, {teensy, Teensy}, _, _, _, _} = Config,

    %% send the authentication results.
    gate_keeper ! {do_match(Sample, Config), Teensy}.



%%
%% 
%%






%% flatten down the tuples into the format that is_match expects
%% namely: {a1,a2,a3,a4,0,b1,b2,b3,b4,0} -- you can have as many points as you want, 
%% but all bikes must have the same number of points

flatten_keys([H|T], Acc) ->
    {bike, _, {thresholds, Thresholds}} = H,
    flatten_keys(T, Acc ++ Thresholds ++ [0]);

flatten_keys([], Acc) ->
    list_to_tuple(Acc).



do_match(Sample, Config) ->

    {config, _, _, 
     {hits_required, Hits}, 
     {activation_threshold, Threshold}, 
     {bikes, Bikes}
    } = Config,
    
    Matches = is_match(Sample, flatten_keys(Bikes,[]), Threshold),
    
    io:format("Matches for Sample ~p, With Keys: ~p  :=: ~p ~n", [Sample, flatten_keys(Bikes, []), Matches]),

    %% We need at least Hits many Matches to make this happen
    if
	Matches >= Hits -> access_granted;
	Matches > 0     -> access_denied;
	true            -> thinking
    end.

		     



%% Internal C Linkages

-define(nif_stub, nif_stub_error(?LINE)).

nif_stub_error(Line) ->
    erlang:nif_error({nif_not_loaded,module,?MODULE,line,Line}).



init() ->
    PrivDir = case code:priv_dir(?MODULE) of
                  {error, bad_name} ->
                      EbinDir = filename:dirname(code:which(?MODULE)),
                      AppPath = filename:dirname(EbinDir),
                      filename:join(AppPath, "priv");
                  Path ->
                      Path
              end,
    erlang:load_nif(filename:join(PrivDir, ?MODULE), 0).


%% the actual C call back 
is_match(Sample,Keys,Threshold) ->
    ?nif_stub.
unlock(Teensy) ->
    ?nif_stub.
blink(Teensy, Color, Times) ->
    ?nif_stub.

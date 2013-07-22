%% @author John L. Singleton <jsinglet@gmail.com>

%% @doc Entry point into the system. Establishes the listeners and sets up the process links to ensure the
%% system keeps running.

-module(main).
-export([start/0]).
%%-compile(export_all).


start() ->
    big_brother:start(defaults:default_config()).


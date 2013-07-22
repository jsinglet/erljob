%% @author John L. Singleton <jsinglet@gmail.com>

%% @doc Defines some program defaults 

-module(defaults).
%%-compile(export_all).
-export([default_config/0,default_bikes/0]).

%% set of default configurations for experimentally observed sportster and crossbones 

default_config() ->
    {config, 
     %% basic parameters
     %% {teensy, "/dev/cu.usbmodem12341"}, % on osx
     {teensy, "/dev/ttyACM0"}, % on linux

     {mic   , "hw:0,0"},
     {hits_required, 6},

     {activation_threshold, 0.01},
     %% the set of bikes to grant access to 
     {bikes, default_bikes()}
     }.

default_bikes() ->
    [
     {bike, {name, "CrossBones"}, {thresholds, [815, 1266]}},
     {bike, {name, "Sporty"}, {thresholds, [2862, 3140]}}
    ].



%% Copyright 2024 Covidien LP.
%% All Rights Reserved. The information contained herein is confidential
%% property of Covidien. The use, copying, transfer or disclosure of such
%% information is prohibited except by written agreement with Covidien.

function ddsUpsCommandPub(block)
    setup(block);
%endfunction

function setup(block)
    SFunHelper.default_setup(block, 0);

    block.NumInputPorts  = 3;
    block.NumOutputPorts = 1;

    % Set the input port properties.
    SFunHelper.init_input_port(block.InputPort(1), 'uint32', 1);
    SFunHelper.init_input_port(block.InputPort(2), 'boolean', 1);
    SFunHelper.init_input_port(block.InputPort(3), ...
    'int32', ...
    1);

    % Set the output port properties.
    SFunHelper.init_output_port(block.OutputPort(1), 'uint32', [1 3]);
    
    %register functions
    block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
    block.RegBlockMethod('Outputs', @Output);
    block.RegBlockMethod('Start', @Start);
    block.RegBlockMethod('Terminate', @Terminate);
    block.RegBlockMethod('WriteRTW', @WriteRTW);
%endfunction

function DoPostPropSetup(block)
    block.NumDworks = 1;

    SFunHelper.init_dwork(block.Dwork(1), 'dds_writer_context', 'uint32', 2);
%endfunction

function Output(block)
%endfunction

function Start(block)
%endfunction

function Terminate(block)
%endfunction

function WriteRTW(block)
%endfunction

classdef SFunHelper
    methods(Static)
        
        function typeid = convert_type_to_typeid(type)
            switch type
                case 'double'
                    typeid = 0;
                case 'single'
                    typeid = 1;
                case 'int8'
                    typeid = 2;
                case 'uint8'
                    typeid = 3;
                case 'int16'
                    typeid = 4;
                case 'uint16'
                    typeid = 5;
                case 'int32'
                    typeid = 6;
                case 'uint32'
                    typeid = 7;
                case 'boolean'
                    typeid = 8;
                otherwise
                    typeid = -1;
            end
        end
        
        function init_dwork(dwork, name, type, dimension)
            dwork.Name            = name;
            dwork.Dimensions      = dimension;
            dwork.DatatypeID      = SFunHelper.convert_type_to_typeid(type);
            dwork.UsedAsDiscState = true;
            dwork.Complexity      = 'Real';
        end
        
        function init_input_port(port, type, dimension)
            port.DatatypeID  = SFunHelper.convert_type_to_typeid(type);
            port.DirectFeedthrough  = 1;
            port.Dimensions  = dimension;
            %port.SampleTime = [-1, 0];
            port.SamplingMode = 'Sample';
        end

        function init_output_port(port, type, dimension)
            port.DatatypeID  = SFunHelper.convert_type_to_typeid(type);
            port.Dimensions  = dimension;
            %port.SampleTime = [-1, 0];
            port.SamplingMode = 'Sample';
        end
        
        function default_setup(block, num_parameters)
            % Set up the port properties to be inherited or dynamic.
            block.SetPreCompInpPortInfoToDynamic;
            block.SetPreCompOutPortInfoToDynamic;
            % Register the parameters.
            block.NumDialogPrms     = num_parameters;
            parameter_tunability = {};
            for i=1:num_parameters
                parameter_tunability(i) = {'NonTunable'};
            end
            block.DialogPrmsTunable = parameter_tunability;
            % Register the sample times.
            %  [-1, 0]               : Inherited sample time
            %block.SampleTimes = [-1 0];
            block.SetAccelRunOnTLC(true);
            block.SimStateCompliance = 'DefaultSimState';
        end
    end
end
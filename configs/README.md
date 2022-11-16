# SCNN Config Preparation

The binary executable ``scnn`` requires one argument that holds the path to the configuration file in order to run a simulation. The example config ``.yaml`` files can be found in the ``configs`` directory. You can modify the ``./configs/config.yaml`` file, or create your own ``.yaml`` file. 

## File Format

The format of the ``yaml`` files is as follows. You must strictly follow this format, or the executable will not run.

1\) Section 1 (Line 1)
* ``Num_Layers``: specify the number of convolutional layers in your simulation

2\) Section 2 (Line 3 ~ 5)
* ``I``: the amount of input activation elements that will be processed by the multiplier array per cycle
* ``F``: the amount of filter weight elements that will be processed by the multiplier array per cycle
* ``defval``: a dummy value, which will be used to fill information such as size of accumulator bank, etc.

3\) Section 3 (Conv Layer Specifications)
* ``N``: batch size of input tensor (default: 1)
* ``C``: number of channels of input tensor
* ``Orig_H``: original height of input tensor
* ``Orig_W``: original width of input tensor
* ``K``: number of output channels
* ``Kc``: size of output channel group (default: 8)
* ``S``: height of filter weight
* ``R``: width of filter weight
* ``PE_Num_H``: number of PEs in the vertical direction (default: 8)
* ``PE_Num_W``: number of PEs in the horizontal direction (default: 8)
* ``io_sparsity``: input activation sparsity (0 being no zero element, 1 being all zeros)
* ``w_sparsity``: filter weight sparsity (0 being no zero element, 1 being all zeros)

Notice that there is an empty line in between each section. In order to increase the number of layers in the simulation, simply change the ``Num_Layers`` in section 1 and add more information using the section 3 format at the end of file. 


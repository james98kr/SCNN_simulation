import torch
import torch.nn as nn
import torch.nn.functional as F
torch.set_printoptions(6)
input_list = [[[ -0.356095,          0,         -0,   0.927671,         -0 ], 
[        -0,         -0,  -0.590956, -0.0371413,         -0 ], 
[        -0,   0.652263,         -0,   0.446294,         -0 ], 
[-0.0843846,          0,   0.676799,         -0,   0.877034 ], 
[        -0, -0.0389948,         -0,         -0,         -0 ]]] 


input_tensor = torch.Tensor(input_list)
weight_list = [[[[ -0.662931,         -0,          0,         -0,         -0 ], 
[         0,   0.195353,  -0.108276,  -0.615379,         -0 ], 
[  0.661747,         -0,          0,          0,   0.418728 ], 
[         0, -0.0787386,  -0.790401,   0.544811,          0 ], 
[        -0,         -0,          0,   0.922436,          0 ]]]]




weight_tensor = torch.Tensor(weight_list)
print(input_tensor.shape, weight_tensor.shape)
output_tensor = F.conv2d(input_tensor, weight_tensor, padding=2)

print(output_tensor.shape)
print(output_tensor)






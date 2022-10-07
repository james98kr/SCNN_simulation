import torch
import torch.nn as nn
import torch.nn.functional as F

input_list = [[[0,0,1,0,2],
            [3,0,0,0,4],
            [0,5,0,0,0],
            [0,0,6,0,7],
            [0,0,0,8,0]], 
            [[9,0,0,10,0],
            [11,12,0,0,0],
            [13,0,0,14,15],
            [0,0,16,0,0],
            [0,17,0,0,18]]]
input_tensor = torch.Tensor(input_list)
weight_list = [[[[0., -9., 0.],
                [5., 0., 0.],
                [4., 0., 0.]],
                [[1., 0., -8.],
                [0., 0., 1.],
                [-6., 0., 9.]]],
                [[[-4., 0., 1.],
                [0., 5., -8.],
                [8., 0., 0.]],
                [[0., 0., -7.],
                [0., 0., 0.],
                [0., 0., 7.]]],
                [[[-9., 3., 0.],
                [3., 7., -5.],
                [0., -5., 6.]],
                [[0., 0., 0.],
                [0., 3., 0.],
                [-9., -4., 6.]]]]
weight_tensor = torch.Tensor(weight_list)
output_tensor = F.conv2d(input_tensor, weight_tensor, padding=1)

print(output_tensor.shape)
print(output_tensor)






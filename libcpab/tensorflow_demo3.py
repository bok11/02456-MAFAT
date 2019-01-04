# -*- coding: utf-8 -*-
"""
Created on Wed Aug 22 09:57:26 2018

@author: nsde
"""
#%%
from libcpab.tensorflow import cpab
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

#%%
if __name__ == '__main__':
    # Lets create some 1D data
    N = 100
    x = np.linspace(0, 1, N)    
    y1 = 1.0/np.sqrt(2*np.pi*0.1**2)*np.exp(-(x-0.5)**2/(2*0.1**2))
    y2 = 1.0/np.sqrt(2*np.pi*0.1**2)*np.exp(-(x-0.4)**2/(2*0.1**2))
    
    # Create transformer
    T = cpab(tess_size=[30,])
    T.fix_data_size([N,]) # fix the data size for speed
    
    
    # Lets do some sampling
    maxiter = 100
    current_sample = T.identity(1)
    current_error = np.linalg.norm(y1 - y2)
    accept_ratio = 0
    for i in tqdm(range(maxiter), desc='mcmc sampling'):
        # Sample random transformations and transform y1
        theta = T.sample_transformation(1, mean=np.squeeze(current_sample))
        y1_trans = T.transform_data(np.expand_dims(y1,0), theta)

        # Calculate error 
        new_error = np.linalg.norm(y1_trans - y2)
        
        # Update rule
        if new_error < current_error:
            current_sample = theta
            current_error = new_error
            accept_ratio += 1
    print('Acceptence ratio: ', accept_ratio / maxiter * 100, '%')
        
    # Show result
    y1_transform = T.transform_data(np.expand_dims(y1, 0), current_sample)
    plt.plot(y1, '-r', label='source')
    plt.plot(y2, 'g-', label='target')
    plt.plot(y1_transform[0], 'b-', label='transformed')
    plt.legend()
    plt.show()

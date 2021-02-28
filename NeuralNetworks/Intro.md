# Neural networks

## What is a Neural Network?

Neural Networks in the artificial intelligence community are an interconnected group of neurons or nodes that uses a mathematical or computational model to process information. They can be used to identify patterns or model complex relationships between inputs and outputs in datasets. They work by having each neuron work as a filter of various types to analyze the data being passed to it. The output from that neuron is computed by some non-linear function of the sum of its inputs. The neurons are usually arranged into layers which may perform different transformations on the data. There are many different variations of neural networks in computing. For example a primitive example of neural networks is the classic work of “Hot Dog or not Hot Dog.” This classic application helps to teach the basics of machine learning as it is an example of a classification neural network. Neural networks learn by observing some labeled input, making a decision, and comparing that to the known result. The network is then rewarded or punished depending on the result and the cycle continues as it continues to train. Your GPU can be used in order to increase the speed at which the neural network trains.

## How to use your GPU with your code

### Using Ubuntu:
In order to ensure that your code is using your AMD GPU, you have to ensure that your user has access to the GPU resources. This can be achieved by adding yourself to the video group using this line
```sudo usermod -a -G video $LOGNAME```

You will then have to reboot your system to make the change to take effect.

You can then double check that your ROCm stack is correct by running the following commands.

```/opt/rocm/bin/rocminfo```

As well as

```/opt/rocm/opencl/bin/x86_64/clinfo```

ROCm also suggests that you add the binaries to the PATH using:

```echo 'export PATH=$PATH:/opt/rocm/bin:/opt/rocm/profiler/bin:/opt/rocm/opencl/bin/x86_64' | sudo tee -a /etc/profile.d/rocm.sh```

If this all went smoothly, then running

```rocm-smi```

should display your hardware information.

The easiest way to get machine learning projects started is with Tensorflow and Keras. We recommend using Docker to get the libraries that you need. Most of these projects are also implemented in python as it makes it simple to write the functions necessary for machine learning.


## Questions
  - [Review questions on this topic](Practice/Questions.md)

## Resources
 - [Train neural networks using AMD GPUs and keras](https://towardsdatascience.com/train-neural-networks-using-amd-gpus-and-keras-37189c453878)
 - [AMD sample code for machine learning](https://github.com/IntuitionMachine/SEEDBank)
 - [Using Keras and Tensorflow with AMD GPU](https://morioh.com/p/0fa4fe33e8bf)

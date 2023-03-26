<span style="font-weight:500;font-size:15px"> The Token Ring network </span> is a ring network in which each node (computer) is connected to two other nodes (successor and predecessor). This type of network uses the token passing access method. There is a special packet called the token that circulates around the ring from one computer to another. In order for a computer on the ring to transmit data, it must wait for a free token. When a computer detects a free token, it can take control of it and transmit data.

The data is transmitted in frames, with additional information (such as addressing) attached to each frame in the form of a header or trailer. A computer cannot transmit data until it has possession of the token. While a token is being used by a computer, other computers cannot transmit data, so there is no competition for the right to transmit data. The token consists of a predefined sequence of bits (a data string) that allows a computer to transfer data through the cable. The architecture of a typical Token Ring network is based on a physical ring. However, the computers in the network are connected to a central hub (a star-wired ring).

When the first computer on the network is turned on, a token is generated. It circulates around the ring, passing through each computer, until one of them signals its intention to transmit data and take control of the token. After capturing the token, the computer sends a data frame onto the network. The frame travels around the ring until it reaches the destination computer. The recipient computer copies the frame into its buffer memory and marks it in the field that contains the state of the frame to indicate that the information has been received. The frame then continues around the ring until it returns to the transmitting computer, where the transmission is validated. The source computer removes the frame from the ring and releases a new token that is transmitted through the ring. At any given time, only one token can be active in the network and it can traverse the ring in only one direction. Requirements:

The Token object should contain:

- Source IP
- Destination IP
- Transmitted message
- Reached destination (Yes/No)
- Available (Yes/No)
- History (the computers through which the token has passed)

A direction for the token is established
Computers in the network are identified by random IP addresses and there can be any number of computers in the network.
After the token is released, it is possible to send another message (choose a new source and destination).

# Packet Measure

- Motivation
- Expectation
- Progress

## Motivation

```
Lab1112 has implemented a system which combines VLC and WIFI. Here the data flow 
is the followinng:
    tcp packet from normal client to relay;
    packet from relay to router via net filter;
    server ack packets to VLC Host;
    packet wrapped by UDP;
    packet from VLC trans to recv;
    packet from recv host to relay via wired;
    packet from relay to client.

So far so good. Let's examine the system closely. 
The first glance is that, packet need to 
modify artifcially at relay, VLC host T&R, also need to pass two routers via wireless, one VLC, two wired. So one question arise,
How to measure packet latency at each phase?
Let's go to origin. Lab1112 assumed that 
VLC has bandwidth with 20MBs, uplink wifi 
with small packet payload, so we could use
VLC as down link candidate for communication with wifi downlink simutaneously, the client from relay with
high priority via modified AIFS. This means that VLC with high bandwidth. Let's see the details. while relay with high workload, this means that uplink packets are many, we
need to allocate priority for relay, otherwise, we need to reduce priority of relay. So question is that how we could predict workload condition and change?


```

## Expectation

1. Measure Packet Latency precisely at each phase;
2. Check that change AIFS could really affect prioiry, which means to 
check that packet with small AIFS could
send more fast than normal.
3. Due to NI device, VLC with high latency???? Can I check that.
4. If  the latency really matters, Can I
change the buffer and timeout at router.



## Progress
1. Measure Packet begin;
2. Throughput test finished;
3. another relay node finished;
4. contribute to recalculate checksum in kernel module;
5. thoughput improvement by define MTU at server with UDP size 1500 B;
6. change AIFS from server packet begins;



# Introduction

Getting ready to start porting my old flight-controller from STM32 + NuttX to XMC4700 + FreeRTOS.

# Modules

## Receiver

### FrSky SBUS

This is a single-pin FrSky 8E2 inverted serial SBUS at 100,000 baud @ 10ms updates with 25 byte encoded packets. Rather than use a per-byte serial interrupt, this code synchronizes to the start of the packet and then uses DMA. This has two benefits.

* 1/25th the number of interrupts
* Each decoding of the packet is for that entire packet, and not the tail of the first packet plus the head of the second packet.

The RX pin of the receiver is used as an interrupt source to measure the time between falling edges. Basically, when the ISR and sync task see >3 ms of dead time, the DMA is activated and the interrupt is shut off. Thus synchronizing the DMA to the receiver. If the first byte of the packet is not the SBUS header byte (0x0F), or the last byte is not the FOOTER (0x00) or FOOTER2 byte (0x04), then a resynchronization is triggered.


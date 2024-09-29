#avrdude -p m1284p -c avrispmkii -P usb -F -U lfuse:r:-:h -U hfuse:r:-:h
/usr/local/CrossPack-AVR/bin/avrdude -p atmega168  -F -c avrisp2 -P usb  -U lfuse:r:-:h -U hfuse:r:-:h

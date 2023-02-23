all: pos.csv bom.csv
	rm -f a2bikelight.zip
	zip a2bikelight.zip *.gbr *.drl

pos.csv: a2bikelight-top-pos.csv
	sed -e 's/Ref,/Designator,/' \
		-e 's/PosX,/Mid X,/' \
		-e 's/PosY,/Mid Y,/' \
		-e 's/Rot,/Rotation,/' \
		-e 's/,Side/,Layer/' \
	< a2bikelight-top-pos.csv > pos.csv

bom.csv: a2bikelight.csv
	cp a2bikelight.csv bom.csv

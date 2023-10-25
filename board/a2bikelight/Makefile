BOARD=a2bikelight

all: pos.csv bom.csv
	rm -f $(BOARD).zip
	zip $(BOARD).zip *.gbr *.drl

bom:
	kicad-cli sch export python-bom --output bom.xml $(BOARD).kicad_sch 


pos.csv: $(BOARD)-top-pos.csv
	sed -e 's/Ref,/Designator,/' \
		-e 's/PosX,/Mid X,/' \
		-e 's/PosY,/Mid Y,/' \
		-e 's/Rot,/Rotation,/' \
		-e 's/,Side/,Layer/' \
	< $(BOARD)-top-pos.csv > pos.csv

bom.csv: $(BOARD).csv
	cp $(BOARD).csv bom.csv

$(BOARD).csv: $(BOARD).kicad_pro
	@echo "bom is out of date"
	@echo "update according to 'kicad to jlcpcb' google doc"
	exit 1

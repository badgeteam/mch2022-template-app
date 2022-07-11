
BASE=`pwd`
for component in appfs bus-i2c i2c-bno055 mch2022-bsp mch2022-rp2040  sdcard spi-ice40 spi-ili9341 ws2812; do
	cd $BASE/components/$component
	git checkout master
	git pull
	cd $BASE
done

for component in i2c-bme680 pax-codecs pax-graphics pax-keyboard; do
	cd $BASE/components/$component
	git checkout main
	git pull
	cd $BASE
done

cd $BASE/tools
git checkout master
git pull
cd $BASE

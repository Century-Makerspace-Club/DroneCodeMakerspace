cd Controller
../arduino-cli.exe compile -b arduino:avr:uno
cd ..

cd Drone
../arduino-cli.exe compile --fqbn arduino:avr:uno
../arduino-cli.exe upload -p COM4 --fqbn arduino:avr:uno Drone
cd ..

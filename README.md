# libvarnam-windows

## Compiling

* Download `libvarnam` into the `deps` directory
* Compile the solution using Visual studio
* Copy the `varnam.dll` to the IMEs debug directory
* Run `regsvr32 VarnamIme.dll` from the `Debug` directory
* Ensure `%ALLUSERSPROFILE%\varnam\schemes` has all the required scheme files
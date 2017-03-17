TODO
=========

Windows IME
----------

* Find out how to put the IME under Malayalam - DONE
* Find out how to type as usual without Malayalam characters appearing in the document
* Hook Varnam instead of the builtin dictionary - DONE
* libvarnam is initialized with full path rather than init_from_id. For some reason init_from_id was failing. Need to find out why this fails - DONE
* Ability to configure the language when initializing libvarnam. Right now `ml` is hard coded 
* Move the hard coded include and link references to libvarnam from the project - DONE
* After typing first word, system goes to a bad state causing issues with next word - DONE
* Support tilda
* Change icons
* Hook Open IME to right shift key
* Currently works only with 32Bit applications. Need to see how to make it 64 bit compatible

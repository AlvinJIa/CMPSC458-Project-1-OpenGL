Project 1 readme file:

Instructions:
	Press the U,I,O to increase transformations
	Press the J,K,L to decrease transformations
	Key alone will alter rotation rate
	Shift+Key will alter scale
	Control+Key will alter translation
	Pressing G will reset transformations
	(Personal extra)
	*Pressing B will reset the camera

	W,A,S,D to move the camera
	Mouse to control the view

What I modified:
File names and line numbers:
	Project1.cpp:
		main() 			line 41
		load image 		line 193-200
		call heightmap		line 212
		box control		line 258-285
		skybox			line 287-355
		heightmap draw		line 359-363
		processInput()		line 384-489
		loadTexture()		line 532-561
	heightmap.hpp:
		Draw()			line 66-90
		make_vertex()		line 117-131
		create_heightmap()	line 135-149
		setup_heightmap()	line 174-194

Everything contained:
	Headers:
		camera.hpp
		heightmap.hpp
		Project1.hpp
		shader.hpp
	Media:
		heightmap/hflab4.jpg
		skybox/arctic-ice_bk.tga
		skybox/arctic-ice_dn.tga
		skybox/arctic-ice_ft.tga
		skybox/arctic-ice_lf.tga
		skybox/arctic-ice_rt.tga
		skybox/arctic-ice_up.tga
		textures/awesomeface.png
`		textures/container.jpg
	Shaders:
		shader.frag
		shader.vert
		shader_SI_P2.vert
	Sources:
		Project1.cpp
	Video:
		Project1_Jia_Ruoyu.mp4		Music & Editing include
	Citation:
		media:
		skybox: The Mighty Pete - 	http://www.petesoasis.com
		Music:	Intro 		-	The xx
		
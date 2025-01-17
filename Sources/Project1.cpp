/*
	Project 1 Submission for CMPSC458
    Name: Ruoyu Jia
	psu id: rxj38
*/

#include <Project1.hpp>

// globals 
	// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

	// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

	// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
	// speed
float   Xspeed, Yspeed, Zspeed = 0.0f;
	// rotation
glm::vec3   objrotation = glm::vec3(0.0f, 0.0f, 0.0f);
	// obj_size
glm::vec3   objsize = glm::vec3(1.0f, 1.0f, 1.0f);
	// position
glm::vec3   objpos = glm::vec3(0.0f, 0.0f, 0.0f);

std::string preamble =
"Project 1 code \n\n"
"Press the U,I,O to increase transformations \n"
"Press the J,K,L to decrease transformations \n"
"\tKey alone will alter rotation rate\n "
"\tShift+Key will alter scale\n "
"\tControl+Key will alter translation\n "
"Pressing G will reset transformations\n ";

int main(int argc, char **argv)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X (left here as legacy, more would need to change)
	#endif

	 // Print Preamble
	std:printf(preamble.c_str());

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project 1: Heightmap", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Set the required callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	// build and compile our shader program (defined in shader.hpp)
	// ------------------------------------
	Shader ourShader("../Project_1/Shaders/shader.vert", "../Project_1/Shaders/shader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes for boxes
	// ------------------------------------------------------------------

	//   3D Coordinates   | Texture Coordinates
	//    x     y     z   |  s     t  
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	//  1.  Create ID / Generate Buffers and for Vertex Buffer Object (VBO), 
	//      Vertex Array Buffer (VAO), and the Element Buffer Objects (EBO)
	unsigned int VBO, VAO, EBO;

	// 2. Bind Vertex Array Object
	glGenVertexArrays(1, &VAO);

	//  Bind the Vertex Buffer
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	// 3. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 4. Copy our indices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 5.  Position attribute for the 3D Position Coordinates and link to position 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 6.  TexCoord attribute for the 2d Texture Coordinates and link to position 2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
	unsigned int box_texture = loadTexture("../Project_1/Media/textures/container.jpg");
	unsigned int smile_texture = loadTexture("../Project_1/Media/textures/awesomeface.png");
	unsigned int front_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_ft.tga");
	unsigned int top_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_up.tga");
	unsigned int bottom_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_dn.tga");
	unsigned int left_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_lf.tga");
	unsigned int right_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_rt.tga");
	unsigned int back_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_bk.tga");


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
					 // either set it manually like so:
	//Setting it using the texture class
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// init heightmap (defined in heightmap.hpp)
	Heightmap heightmap("../Project_1/Media/heightmaps/hflab4.jpg");
	//Heightmap heightmap("../Project_1/Media/heightmaps/heightmap.jpg"); 
	//Heightmap heightmap("../Project_1/Media/skybox/arctic-ice_dn.tga");
	unsigned int heightmap_texture = loadTexture("../Project_1/Media/skybox/arctic-ice_dn.tga");
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		// Set background color (shouldn't need it in the end b/c the box should fully cover everything
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units in fragment shader
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, box_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, smile_texture);

		// activate shader
		ourShader.use();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		
		// render boxes
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			// Translate the model to the cube starting position
			model = glm::translate(model, cubePositions[i]);
			// Rotate the cube by an angle
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));

			objrotation.x += deltaTime * Xspeed;
			objrotation.y += deltaTime * Yspeed;
			objrotation.z += deltaTime * Zspeed;
			model = glm::rotate(model, glm::radians(objrotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(objrotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(objrotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			
			model = glm::scale(model, objsize);

			model = glm::translate(model, objpos);

			// Set model in shader
			ourShader.setMat4("model", model);

			// Draw the box with triangles
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glm::mat4 view1 = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		ourShader.setMat4("view", view1);
		// Bind new textures to boh texture positions (do both since it has 2 textures in the vertex shader)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, front_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, front_texture);

		// Make the model for one wall and shift/scale it
		glm::mat4 model;
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		
		// Set model in shader
		ourShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, top_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, top_texture);
		glm::mat4 model_top;
		model_top = glm::rotate(model_top, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_top = glm::rotate(model_top, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model_top = glm::scale(model_top, glm::vec3(100.0f, 100.0f, 100.0f));	
		ourShader.setMat4("model", model_top);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, right_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, right_texture);
		glm::mat4 model_right;
		model_right = glm::rotate(model_right, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model_right = glm::scale(model_right, glm::vec3(100.0f, 100.0f, 100.0f));
		ourShader.setMat4("model", model_right);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, left_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, left_texture);
		glm::mat4 model_left;
		model_left = glm::rotate(model_left, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model_left = glm::scale(model_left, glm::vec3(100.0f, 100.0f, 100.0f));
		ourShader.setMat4("model", model_left);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, bottom_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, bottom_texture);
		glm::mat4 model_bottom;
		model_bottom = glm::rotate(model_bottom, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model_bottom = glm::rotate(model_bottom, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model_bottom = glm::scale(model_bottom, glm::vec3(100.0f, 100.0f, 100.0f));
		ourShader.setMat4("model", model_bottom);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, back_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, back_texture);
		glm::mat4 model_back;
		model_back = glm::rotate(model_back, glm::radians(180.0f), glm::vec3(1.0f, 1.0f, 0.0f));
		model_back = glm::rotate(model_back, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model_back = glm::scale(model_back, glm::vec3(100.0f, 100.0f, 100.0f));
		ourShader.setMat4("model", model_back);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//glm::mat4 view1 = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		//ourShader.setMat4("view", view1);
		ourShader.setMat4("view", view);


		// Draw the heightmap (defined in heightmap.hpp)  Similar to above but you have to write it.
		heightmap.Draw(ourShader, heightmap_texture);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	glm::mat4 model;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Xspeed += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Yspeed += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Zspeed += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Xspeed -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Yspeed -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
		&& (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
		)
		Zspeed -= 1.0f;


	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		objsize.x += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		objsize.y += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		objsize.z += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		objsize.x -= 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		objsize.y -= 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		objsize.z -= 0.1f;

	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		objpos.x += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		objpos.y += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		objpos.z += 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		objpos.x -= 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		objpos.y -= 0.1f;
	if ((glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		&& glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		objpos.z -= 0.1f;

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		Xspeed = 0; Yspeed = 0; Zspeed = 0;
		objrotation = glm::vec3(0.0f, 0.0f, 0.0f);
		objsize = glm::vec3(1.0f, 1.0f, 1.0f);
		objpos = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);
		camera.Front = glm::vec3(0.0f, 0.0f, -1.0f);
		camera.WorldUp = glm::vec3(0.0f, 0.1f, 0.0f);
		camera.Yaw = -90.0f;
		camera.Pitch = 0.0f;
		camera.Zoom = 45.0f;
		float lastX = 0.0f;
		float lastY = 0.0f;
		bool firstMouse = true;
		camera.ProcessMouseMovement(lastX, lastY);
	}
	// Add other key operations here.  
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height) ;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}



// utility function for loading a 2D texture from file - Note, you might want to create another function for this with GL_CLAMP_TO_EDGE for the texture wrap param
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}



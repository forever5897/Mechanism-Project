package lightSet;

import static javax.media.opengl.GL.GL_FRONT;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_AMBIENT;
import static javax.media.opengl.fixedfunc.GLLightingFunc.GL_EMISSION;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;

public class Light_Material {

	public Light_Material() {

	}

	private void Light0(GL2 gl) {

		gl.glEnable(GL2.GL_LIGHT0);
		float position[] = { 40.0f, 80.0f, 530.0f, 1 };
		gl.glLightfv(GL2.GL_LIGHT0, GL2.GL_POSITION, position, 0);
		float intensity[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT0, GL2.GL_DIFFUSE, intensity, 0);
		float ambientLight[] = { 0.07f, 0.07f, 0.07f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT0, GL_AMBIENT, ambientLight, 0);
		float specular[] = { 0.3f, 0.1f, 0.1f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT0, GL2.GL_SPECULAR, specular, 0);

	}

	private void Light1(GL2 gl) {

		gl.glEnable(GL2.GL_LIGHT1);
		float position[] = { -50.0f, -40.0f, 400.0f, 1 };
		gl.glLightfv(GL2.GL_LIGHT1, GL2.GL_POSITION, position, 0);
		float intensity[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT1, GL2.GL_DIFFUSE, intensity, 0);
		float ambientLight[] = { 0.07f, 0.07f, 0.07f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT1, GL_AMBIENT, ambientLight, 0);
		float specular[] = { 0.3f, 0.3f, 0.1f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT1, GL2.GL_SPECULAR, specular, 0);

	}

	private void Light2(GL2 gl) {

		float position[] = { 100.0f, -150.0f, 190.0f, 1 };
		gl.glLightfv(GL2.GL_LIGHT2, GL2.GL_POSITION, position, 0);
		float intensity[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT2, GL2.GL_DIFFUSE, intensity, 0);
		float ambientLight[] = { 0.07f, 0.07f, 0.07f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT2, GL_AMBIENT, ambientLight, 0);
		float specular[] = { 0.3f, 0.3f, 0.1f, 1.0f };
		gl.glLightfv(GL2.GL_LIGHT2, GL2.GL_SPECULAR, specular, 0);
		gl.glEnable(GL2.GL_LIGHT2);

	}

	public void Lights(GL2 gl) {

		Light0(gl);
		Light1(gl);
		Light2(gl);
	}

	public void LightMaterial(GL2 gl) {

		gl.glEnable(GL2.GL_COLOR_MATERIAL);
		gl.glColorMaterial(GL.GL_FRONT_AND_BACK, GL2.GL_AMBIENT_AND_DIFFUSE);
		float specColor[] = {1, 1, 1, 1};
		gl.glMaterialfv(GL.GL_FRONT_AND_BACK, GL2.GL_SPECULAR, specColor, 0);
		gl.glMaterialf(GL.GL_FRONT_AND_BACK, GL2.GL_SHININESS, 80);
		float emission[] = { 0.0f, 0.0f, 0.001f, 1.0f };
		gl.glMaterialfv(GL_FRONT, GL_EMISSION, emission, 0);
	}
}

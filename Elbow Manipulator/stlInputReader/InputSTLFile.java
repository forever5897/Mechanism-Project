package stlInputReader;



import geometry.s3d.solid.Stl;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;

public class InputSTLFile {

	private float[] data;

	public InputSTLFile(Stl Data) {
		// TODO Auto-generated constructor stub
		this.data = Data.getArray();
	}

	public void draw(GL2 gl) {

		// gl.glPushMatrix();
		// gl.glRotatef(-90, 1, 0, 0);

		gl.glBegin(GL.GL_TRIANGLES);
		for (int i = 0; i < data.length; i++) {
			gl.glNormal3f(data[i++], data[i++], data[i++]);
			gl.glVertex3f(data[i++], data[i++], data[i++]);
			gl.glVertex3f(data[i++], data[i++], data[i++]);
			gl.glVertex3f(data[i++], data[i++], data[i++]);
			i -= 1;
		}
		gl.glEnd();
		// gl.glPopMatrix();

	}

	public float[] getData() {
		return data;
	}
	
}

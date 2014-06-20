package elbow_manipulator;

import geometry.s3d.solid.Stl;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.GLException;
import javax.media.opengl.awt.GLJPanel;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import lightSet.Light_Material;
import stlInputReader.InputSTLFile;

import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureIO;

public class ElbowArm extends JFrame implements ChangeListener, DocumentListener, ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private int[] m_MouseDownPoint = { Integer.MAX_VALUE, Integer.MAX_VALUE };
	private double theta1 = 0, theta2 = 0, theta3 = 0, theta4 = 0, theta5 = 0,
			      theta6 = 0, theta234 = 0;
	private double temp_theta1 = 0, temp_theta2 = 0, temp_theta3 = 0, temp_theta4 = 0,
				   temp_theta5 = 0, temp_theta6 = 0;
	private double temp_theta1_1 = 0, temp_theta2_1 = 0, temp_theta3_1 = 0, temp_theta4_1 = 0,
				   temp_theta5_1 = 0, temp_theta6_1 = 0;
	private boolean cuboidFlag = false, signalFlag = false;    //cuboidFlag判斷是否要繪製長方體
															   //signalFlag末位置判斷旗標
	private Light_Material setLight = new Light_Material();
	private Texture t;
	private float[] u1 = {0, 0, 0}, v1 = {0, 0, 0}, w1 = {0, 0, 0}, Q1 = {0, 0, 0};
	private float[] u2 = {0, 0, 0}, v2 = {0, 0, 0}, w2 = {0, 0, 0}, Q2 = {0, 0, 0};
	private float[] pos1 = {0, 0, 0}, pos2 = {0, 0, 0}, temp_pos = {0, 0, 0};
	private float[] temp_u = {0, 0, 0}, temp_v = {0, 0, 0}, temp_w = {0, 0, 0}, temp_Q = {0, 0, 0};
	private int t_span = 50;                                 //動畫格數預設為100格
	private boolean stateFlag = true;                         //兩段動畫判斷旗標
	private boolean LocationFlag = false;                     //判斷此次輸入為第幾次輸入變數
	private boolean AnimateFlag = true;
	private int index = 0;
	
	// setting elbow manipulator
	private Stl base = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/base.stl"));
	private InputSTLFile base_Data = new InputSTLFile(base);
	private Stl link1 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link1.stl"));
	private InputSTLFile link1_Data = new InputSTLFile(link1);
	private Stl link2 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link2.stl"));
	private InputSTLFile link2_Data = new InputSTLFile(link2);
	private Stl link3 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link3.stl"));
	private InputSTLFile link3_Data = new InputSTLFile(link3);
	private Stl link4 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link4.stl"));
	private InputSTLFile link4_Data = new InputSTLFile(link4);
	private Stl link5 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link5.stl"));
	private InputSTLFile link5_Data = new InputSTLFile(link5);
	private Stl link6 = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/link6.stl"));
	private InputSTLFile link6_Data = new InputSTLFile(link6);
	private Stl cuboid = new Stl(new File("D:/Course/CCU/Mechanism/Elbow arm/cuboid.stl"));
	private InputSTLFile cuboid_Data = new InputSTLFile(cuboid);
	
	private Inverse inverseCal;
	private float width = 1, height = 1, m_xangle = 0, m_yangle = 0;

	// Java Swing setting
	private JPanel pane1, pane3;
	private GLCapabilities capabilities = new GLCapabilities(null);
	private final GLJPanel pane2 = new GLJPanel(capabilities);
	private JLabel jLabel1, jLabel2, jLabel3, jLabel4, jLabel5, jLabel6;
	private JSlider jSlider1, jSlider2, jSlider3, jSlider4, jSlider5, jSlider6;
	private JLabel uLabel, vLabel, wLabel, posLabel;
	private JTextField jTextField1, jTextField2, jTextField3, jTextField4, jTextField5,
					   jTextField6, jTextField7, jTextField8, jTextField9, jTextField10,
					   jTextField11, jTextField12;
	private JButton renewButton, animateButton, variableButton;
	private Timer timer;
	
	public ElbowArm() throws FileNotFoundException, IOException {
		// TODO Auto-generated constructor stub
		super();
		initGUI();
		initSet();
	}

	public static void main(String[] args) throws FileNotFoundException, IOException {
		// TODO Auto-generated method stub
		ElbowArm frame = new ElbowArm();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}

	public class GraphicListener implements GLEventListener {

		@Override
		public void display(GLAutoDrawable arg0) {
			// TODO Auto-generated method stub
			GL2 gl = arg0.getGL().getGL2();

			gl.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT
					| GL.GL_STENCIL_BUFFER_BIT);

			gl.glEnable(GL.GL_DEPTH_TEST);
			gl.glCullFace(GL.GL_FRONT);
			gl.glFrontFace(GL.GL_CCW);

			gl.glMatrixMode(GL2.GL_PROJECTION);
			gl.glLoadIdentity();
			gl.glScalef(600 / width, 600 / height, 1);

			gl.glRotatef(90, 1, 0, 0);
			gl.glRotatef(-45, 0, 0, 1);
			gl.glRotatef(-30, 1, 1, 0);

			gl.glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);

			gl.glMatrixMode(GL2.GL_MODELVIEW);
			gl.glLoadIdentity();
			gl.glScalef(0.8f, 0.8f, 0.8f);
			gl.glRotatef(m_yangle, 1, 0, 0);
			gl.glRotatef(m_xangle, 0, 1, 0);

			gl.glEnable(GL2.GL_LIGHTING);
			gl.glColor3f(1, 0.5f, 0.5f);
			
			if(stateFlag) {
				// //////elbow manipulator setting////////
				gl.glPushMatrix();
				gl.glRotatef(-90, 0, 0, 1);
				base_Data.draw(gl);

				gl.glColor3f(0.5f, 0.5f, 0.75f);
				gl.glTranslatef(0, 0, 100);
				gl.glRotated(theta1, 0, 0, 1);
				link1_Data.draw(gl);

				gl.glColor3f(0.2f, 0.7f, 0.75f);
				gl.glRotatef(90, 1, 0, 0);
				gl.glRotatef(90, 0, 1, 0);
				gl.glTranslatef(0, 300, 0);
				gl.glRotated(theta2, 0, 0, 1);
				link2_Data.draw(gl);

				gl.glColor3f(0.3f, 0.4f, 0.7f);
				gl.glTranslatef(300, 0, 0);
				gl.glRotated(theta3, 0, 0, 1);
				link3_Data.draw(gl);

				gl.glColor3f(1.f, 0.5f, 0.5f);
				gl.glTranslatef(250, 0, 0);
				gl.glRotated(theta4, 0, 0, 1);
				link4_Data.draw(gl);

				gl.glColor3f(1, 0.25f, 0);
				gl.glRotatef(-90, 1, 0, 0);
				gl.glTranslatef(175, 0, 0);
				gl.glRotated(theta5, 0, 0, 1);
				link5_Data.draw(gl);

				gl.glColor3f(0.5f, 0.5f, 0.75f);
				gl.glRotatef(90, 0, 1, 0);
				gl.glTranslatef(0, 0, 45);
				gl.glRotated(theta6, 0, 0, 1);
				link6_Data.draw(gl);

				// 回歸到世界座標軸
				gl.glTranslatef(0, 0, 187.5f);
				gl.glRotatef(-180, 0, 0, 1);
				gl.glDisable(GL2.GL_LIGHTING);
				DrawAxis(gl, false);
				gl.glPopMatrix();
				// //////////////////////////////////////
			}else {
				// //////elbow manipulator setting////////
				gl.glPushMatrix();
				gl.glRotatef(-90, 0, 0, 1);
				base_Data.draw(gl);

				gl.glColor3f(0.5f, 0.5f, 0.75f);
				gl.glTranslatef(0, 0, 100);
				gl.glRotated(theta1 + temp_theta1_1 * 50, 0, 0, 1);
				link1_Data.draw(gl);

				gl.glColor3f(0.2f, 0.7f, 0.75f);
				gl.glRotatef(90, 1, 0, 0);
				gl.glRotatef(90, 0, 1, 0);
				gl.glTranslatef(0, 300, 0);
				gl.glRotated(theta2 + temp_theta2_1 * 50, 0, 0, 1);
				link2_Data.draw(gl);

				gl.glColor3f(0.3f, 0.4f, 0.7f);
				gl.glTranslatef(300, 0, 0);
				gl.glRotated(theta3 + temp_theta3_1 * 50, 0, 0, 1);
				link3_Data.draw(gl);

				gl.glColor3f(1.f, 0.5f, 0.5f);
				gl.glTranslatef(250, 0, 0);
				gl.glRotated(theta4 + temp_theta4_1 * 50, 0, 0, 1);
				link4_Data.draw(gl);

				gl.glColor3f(1, 0.25f, 0);
				gl.glRotatef(-90, 1, 0, 0);
				gl.glTranslatef(175, 0, 0);
				gl.glRotated(theta5 + temp_theta5_1 * 50, 0, 0, 1);
				link5_Data.draw(gl);

				gl.glColor3f(0.5f, 0.5f, 0.75f);
				gl.glRotatef(90, 0, 1, 0);
				gl.glTranslatef(0, 0, 45);
				gl.glRotated(theta6 + temp_theta6_1 * 50, 0, 0, 1);
				link6_Data.draw(gl);

				// 回歸到世界座標軸
				gl.glTranslatef(0, 0, 187.5f);
				gl.glRotatef(-180, 0, 0, 1);
				gl.glDisable(GL2.GL_LIGHTING);
				DrawAxis(gl, false);
				if(cuboidFlag == false) {
					gl.glEnable(GL2.GL_LIGHTING);
					cuboid_Data.draw(gl);
				}
				gl.glPopMatrix();
				// //////////////////////////////////////
			}
			
			if(cuboidFlag) {
				gl.glPushMatrix();
				gl.glTranslatef(Q1[0], Q1[1], Q1[2]);
				DrawArbitraryAxis(gl, true);
				gl.glColor3f(0.95f, 0.95f, 0.15f);
				cuboid_Data.draw(gl);
				gl.glPopMatrix();
			} else {
				gl.glPushMatrix();
				gl.glTranslatef(Q2[0], Q2[1], Q2[2]);
				DrawArbitraryAxis(gl, false);
				gl.glColor3f(1, 1, 1);
				cuboid_Data.draw(gl);
				gl.glPopMatrix();
			}
			if(signalFlag == true) {
				gl.glPushMatrix();
				gl.glTranslatef(Q2[0], Q2[1], Q2[2]);
				DrawArbitraryAxis(gl, false);
				gl.glColor3f(1, 1, 1);
				cuboid_Data.draw(gl);
				gl.glPopMatrix();
			}
			
			gl.glDisable(GL2.GL_LIGHTING);
			DrawAxis(gl, true);

			gl.glEnable(GL2.GL_LIGHTING);
			DrawFloor(gl);

		}

		@Override
		public void dispose(GLAutoDrawable arg0) {
			// TODO Auto-generated method stub

		}

		@Override
		public void init(GLAutoDrawable arg0) {
			// TODO Auto-generated method stub
			GL2 gl = arg0.getGL().getGL2();
			gl.glClearColor(0.5f, 0.5f, 0.5f, 0);

			try {
				gl.glEnable(GL.GL_TEXTURE_2D);
				t = TextureIO.newTexture(new File("C:/Users/Daniel/workspace/Mechanism/images.bmp"), true);
				t.bind(gl);
			} catch (GLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			gl.glEnable(GL2.GL_LIGHTING);
			setLight.Lights(gl);
			setLight.LightMaterial(gl);

		}

		@Override
		public void reshape(GLAutoDrawable arg0, int arg1, int arg2, int arg3,
				int arg4) {
			// TODO Auto-generated method stub
			width = arg3;
			height = arg4;
		}

	}

	private void DrawAxis(GL2 gl, boolean typeFlag) {

		if (typeFlag) {
			gl.glNewList(1, GL2.GL_COMPILE_AND_EXECUTE);
			gl.glLineWidth(4);
			// Draw axis line
			gl.glBegin(GL.GL_LINES);
			// x axis is red
			gl.glColor3f(1, 0, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(800, 0, 0);
			// y axis is green
				gl.glColor3f(0, 1, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(0, 800, 0);
			// z axis is blue
				gl.glColor3f(0, 0, 1);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(0, 0, 800);
			gl.glEnd();
			gl.glEndList();
		} else {
			gl.glNewList(2, GL2.GL_COMPILE_AND_EXECUTE);
			gl.glLineWidth(1.0f);
			// Draw axis line
			gl.glBegin(GL.GL_LINES);
			// x axis is red
				gl.glColor3f(1, 0, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(300, 0, 0);
			// y axis is green
				gl.glColor3f(0, 1, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(0, 300, 0);
			// z axis is blue
				gl.glColor3f(0, 0, 1);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(0, 0, 300);
			gl.glEnd();
			gl.glEndList();
		}
	}

	private void DrawFloor(GL2 gl) {

		gl.glBegin(GL2.GL_QUADS);
		gl.glNormal3f(0.0f, 0.0f, 1.0f);

		gl.glTexCoord2f(0, 1);
		gl.glVertex3f(-1000, 1000, 0);

		gl.glTexCoord2f(0, 0);
		gl.glVertex3f(-1000, -1000, 0);

		gl.glTexCoord2f(1, 0);
		gl.glVertex3f(1000, -1000, 0);

		gl.glTexCoord2f(1, 1);
		gl.glVertex3f(1000, 1000, 0);

		gl.glEnd();
	}

	private void DrawArbitraryAxis(GL2 gl, boolean typeFlag) {
		if(typeFlag) {
			gl.glLineWidth(1.5f);
			gl.glNewList(1, GL2.GL_COMPILE_AND_EXECUTE);
			gl.glBegin(GL.GL_LINES);
			// u axis is red
				gl.glColor3f(1, 0, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(u1[0] * 100, u1[1] * 100, u1[2] * 100);
			// v axis is green
				gl.glColor3f(0, 1, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(v1[0] * 100, v1[1] * 100, v1[2] * 100);
			// w axis is blue
				gl.glColor3f(0, 0, 1);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(w1[0] * 100, w1[1] * 100, w1[2] * 100);
			gl.glEnd();
			gl.glEndList();
		} else {
			gl.glLineWidth(1.5f);
			gl.glNewList(2, GL2.GL_COMPILE_AND_EXECUTE);
			gl.glBegin(GL.GL_LINES);
			// u axis is red
				gl.glColor3f(1, 0, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(u2[0] * 100, u2[1] * 100, u2[2] * 100);
			// v axis is green
				gl.glColor3f(0, 1, 0);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(v2[0] * 100, v2[1] * 100, v2[2] * 100);
			// w axis is blue
				gl.glColor3f(0, 0, 1);
				gl.glVertex3f(0, 0, 0);
				gl.glVertex3f(w2[0] * 100, w2[1] * 100, w2[2] * 100);
				gl.glEnd();
			gl.glEndList();
		}
		
	}
	private void initGUI() {
		setSize(1065, 600);
		setTitle("Mechanism Homework");
		getContentPane().setLayout(null);
		pane1 = new JPanel();
		pane1.setLayout(null);
		getContentPane().add(pane1);
		pane1.setBounds(0, 0, 350, 320);
		pane1.setBorder(BorderFactory.createTitledBorder("Axis Control"));
		{
			jLabel1 = new JLabel();
			pane1.add(jLabel1, "1, 0");
			jLabel1.setText("Theta1");
			jLabel1.setBounds(45, 35, 40, 20);
		}
		{
			jLabel2 = new JLabel();
			pane1.add(jLabel2, "2, 0");
			jLabel2.setText("Theta2");
			jLabel2.setBounds(45, 80, 40, 20);
		}

		{
			jLabel3 = new JLabel();
			pane1.add(jLabel3, "1, 0");
			jLabel3.setText("Theta3");
			jLabel3.setBounds(45, 125, 40, 20);
		}
		{
			jLabel4 = new JLabel();
			pane1.add(jLabel4, "1, 0");
			jLabel4.setText("Theta4");
			jLabel4.setBounds(45, 170, 40, 20);
		}
		{
			jLabel5 = new JLabel();
			pane1.add(jLabel5, "1, 0");
			jLabel5.setText("Theta5");
			jLabel5.setBounds(45, 210, 40, 20);
		}
		{
			jLabel6 = new JLabel();
			pane1.add(jLabel6, "1, 0");
			jLabel6.setText("Theta6");
			jLabel6.setBounds(45, 255, 40, 20);
		}
		{
			jSlider1 = new JSlider(0, 360, 0);
			pane1.add(jSlider1);
			jSlider1.setBounds(90, 30, 200, 45);
			jSlider1.addChangeListener(this);
			jSlider1.setPaintTicks(true);
			jSlider1.setMajorTickSpacing(90);
			jSlider1.setMinorTickSpacing(15);
			jSlider1.setPaintLabels(true);
			jSlider1.setPaintTrack(true);
			jSlider1.setSnapToTicks(true);
		}
		{
			jSlider2 = new JSlider(-15, 195, 0);
			pane1.add(jSlider2, "0, 1");
			jSlider2.setBounds(90, 75, 200, 45);
			jSlider2.addChangeListener(this);
			jSlider2.setPaintTicks(true);
			jSlider2.setMajorTickSpacing(90);
			jSlider2.setMinorTickSpacing(15);
			jSlider2.setPaintLabels(true);
			jSlider2.setPaintTrack(true);
			jSlider2.setSnapToTicks(true);
		}
		{
			jSlider3 = new JSlider(-95, 95, 0);
			pane1.add(jSlider3, "1, 1");
			jSlider3.setBounds(90, 120, 200, 45);
			jSlider3.addChangeListener(this);
			jSlider3.setPaintTicks(true);
			jSlider3.setMajorTickSpacing(90);
			jSlider3.setMinorTickSpacing(15);
			jSlider3.setPaintLabels(true);
			jSlider3.setPaintTrack(true);
			jSlider3.setSnapToTicks(true);
		}
		{
			jSlider4 = new JSlider(-100, 100, 0);
			theta4 = jSlider4.getValue();
			pane1.add(jSlider4);
			jSlider4.setBounds(90, 165, 200, 45);
			jSlider4.addChangeListener(this);
			jSlider4.setPaintTicks(true);
			jSlider4.setMajorTickSpacing(90);
			jSlider4.setMinorTickSpacing(15);
			jSlider4.setPaintLabels(true);
			jSlider4.setPaintTrack(true);
			jSlider4.setSnapToTicks(true);
		}
		{
			jSlider5 = new JSlider(-100, 100, 0);
			pane1.add(jSlider5);
			jSlider5.setBounds(90, 210, 200, 45);
			jSlider5.addChangeListener(this);
			jSlider5.setPaintTicks(true);
			jSlider5.setMajorTickSpacing(90);
			jSlider5.setMinorTickSpacing(15);
			jSlider5.setPaintLabels(true);
			jSlider5.setPaintTrack(true);
			jSlider5.setSnapToTicks(true);
		}
		{
			jSlider6 = new JSlider(0, 360, 0);
			pane1.add(jSlider6);
			jSlider6.setBounds(90, 255, 200, 45);
			jSlider6.addChangeListener(this);
			jSlider6.setPaintTicks(true);
			jSlider6.setMajorTickSpacing(90);
			jSlider6.setMinorTickSpacing(15);
			jSlider6.setPaintLabels(true);
			jSlider6.setPaintTrack(true);
			jSlider6.setSnapToTicks(true);
		}
		pane3 = new JPanel();
		pane3.setLayout(null);
		getContentPane().add(pane3);
		pane3.setBounds(0, 320, 350, 240);
		pane3.setBorder(BorderFactory.createTitledBorder("Inverse Kinematics"));
		{
			uLabel = new JLabel();
			pane3.add(uLabel);
			uLabel.setText("u axis:");
			uLabel.setBounds(26, 23, 50, 20);
		}
		{
			jTextField1 = new JTextField();
			pane3.add(jTextField1);
			jTextField1.setText("0.0");
			jTextField1.setBounds(80, 20, 70, 25);
			jTextField1.getDocument().addDocumentListener(this);
		}
		{
			jTextField2 = new JTextField();
			pane3.add(jTextField2);
			jTextField2.setText("0.0");
			jTextField2.setBounds(160, 20, 70, 25);
			jTextField2.getDocument().addDocumentListener(this);
		}
		{
			jTextField3 = new JTextField();
			pane3.add(jTextField3);
			jTextField3.setText("1.0");
			jTextField3.setBounds(240, 20, 70, 25);
			jTextField3.getDocument().addDocumentListener(this);
		}
		{
			vLabel = new JLabel();
			pane3.add(vLabel);
			vLabel.setText("v axis:");
			vLabel.setBounds(26, 53, 50, 20);
		}
		{
			jTextField4 = new JTextField();
			pane3.add(jTextField4);
			jTextField4.setText("0.0");
			jTextField4.setBounds(80, 50, 70, 25);
			jTextField4.getDocument().addDocumentListener(this);
		}
		{
			jTextField5 = new JTextField();
			pane3.add(jTextField5);
			jTextField5.setText("-1.0");
			jTextField5.setBounds(160, 50, 70, 25);
			jTextField5.getDocument().addDocumentListener(this);
		}
		{
			jTextField6 = new JTextField();
			pane3.add(jTextField6);
			jTextField6.setText("0.0");
			jTextField6.setBounds(240, 50, 70, 25);
			jTextField6.getDocument().addDocumentListener(this);
		}
		{
			wLabel = new JLabel();
			pane3.add(wLabel);
			wLabel.setText("w axis:");
			wLabel.setBounds(26, 83, 50, 20);
		}
		{
			jTextField7 = new JTextField();
			pane3.add(jTextField7);
			jTextField7.setText("1.0");
			jTextField7.setBounds(80, 80, 70, 25);
			jTextField7.getDocument().addDocumentListener(this);
		}
		{
			jTextField8 = new JTextField();
			pane3.add(jTextField8);
			jTextField8.setText("0.0");
			jTextField8.setBounds(160, 80, 70, 25);
			jTextField8.getDocument().addDocumentListener(this);
		}
		{
			jTextField9 = new JTextField();
			pane3.add(jTextField9);
			jTextField9.setText("0.0");
			jTextField9.setBounds(240, 80, 70, 25);
			jTextField9.getDocument().addDocumentListener(this);
		}
		{
			posLabel = new JLabel();
			pane3.add(posLabel);
			posLabel.setText("Position:");
			posLabel.setBounds(26, 113, 50, 20);
		}
		{
			jTextField10 = new JTextField();
			pane3.add(jTextField10);
			jTextField10.setText("200");
			jTextField10.setBounds(80, 110, 70, 25);
			jTextField10.getDocument().addDocumentListener(this);
		}
		{
			jTextField11 = new JTextField();
			pane3.add(jTextField11);
			jTextField11.setText("300");
			jTextField11.setBounds(160, 110, 70, 25);
			jTextField11.getDocument().addDocumentListener(this);
		}
		{
			jTextField12 = new JTextField();
			pane3.add(jTextField12);
			jTextField12.setText("500");
			jTextField12.setBounds(240, 110, 70, 25);
			jTextField12.getDocument().addDocumentListener(this);
		}
		{
			timer = new Timer(100, this);
		}
		{
			renewButton = new JButton();
			pane3.add(renewButton);
			renewButton.setText("Locate");
			renewButton.setBounds(10, 150, 100, 55);
			renewButton.addActionListener(this);
		{
			animateButton = new JButton();
			pane3.add(animateButton);
			animateButton.setText("Animate");
			animateButton.setBounds(120, 150, 100, 55);
			animateButton.addActionListener(this);
			animateButton.setEnabled(false);
		}
		{
			variableButton = new JButton("Variables");
			pane3.add(variableButton);
			variableButton.setBounds(230, 150, 100, 55);
			variableButton.addActionListener(this);
		}
		capabilities.setDoubleBuffered(true);
		GraphicListener listener = new GraphicListener();
		pane2.addGLEventListener(listener);
		getContentPane().add(pane2);
		pane2.setBounds(350, 0, 700, 560);
		pane2.setBorder(BorderFactory.createTitledBorder("Elbow Manipulator Simulation"));
		
		
		pane2.addMouseListener(new MouseAdapter() {
			public void mouseReleased(MouseEvent e) {
				m_MouseDownPoint[0] = Integer.MAX_VALUE;
				m_MouseDownPoint[1] = Integer.MAX_VALUE;
			}
		});

		pane2.addMouseMotionListener(new MouseMotionAdapter() {
			public void mouseDragged(MouseEvent e) {
				if (m_MouseDownPoint[0] == Integer.MAX_VALUE
						|| m_MouseDownPoint[1] == Integer.MAX_VALUE) {
					m_MouseDownPoint[0] = e.getX();
					m_MouseDownPoint[1] = e.getY();
				}
				m_xangle += (e.getX() - m_MouseDownPoint[0]) / 3.6;
				m_yangle += (e.getY() - m_MouseDownPoint[1]) / 3.6;
				pane2.repaint();
				m_MouseDownPoint[0] = e.getX();
				m_MouseDownPoint[1] = e.getY();
			}
		});
	}
}

	@Override
	public void stateChanged(ChangeEvent arg0) {
		if ((JSlider) arg0.getSource() == jSlider1) {
			theta1 = jSlider1.getValue();
			pane2.repaint();
		}
		if ((JSlider) arg0.getSource() == jSlider2) {
			theta2 = jSlider2.getValue();
			pane2.repaint();
		}
		if ((JSlider) arg0.getSource() == jSlider3) {
			theta3 = jSlider3.getValue();
			pane2.repaint();
		}
		if ((JSlider) arg0.getSource() == jSlider4) {
			theta4 = jSlider4.getValue();
			pane2.repaint();
		}
		if ((JSlider) arg0.getSource() == jSlider5) {
			theta5 = jSlider5.getValue();
			pane2.repaint();
		}
		if ((JSlider) arg0.getSource() == jSlider6) {
			theta6 = jSlider6.getValue();
			pane2.repaint();
		}
	}

	@Override
	public void changedUpdate(DocumentEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		//u component
		if(e.getDocument() == jTextField1.getDocument()) {
			temp_u[0] = Float.parseFloat(jTextField1.getText());
		}
		if(e.getDocument() == jTextField2.getDocument()) {
			temp_u[1] = Float.parseFloat(jTextField2.getText());
		}
		if(e.getDocument() == jTextField3.getDocument()) {
			temp_u[2] = Float.parseFloat(jTextField3.getText());
		}
		//v component
		if(e.getDocument() == jTextField4.getDocument()) {
			temp_v[0] = Float.parseFloat(jTextField4.getText());
		}
		if(e.getDocument() == jTextField5.getDocument()) {
			temp_v[1] = Float.parseFloat(jTextField5.getText());
		}
		if(e.getDocument() == jTextField6.getDocument()) {
			temp_v[2] = Float.parseFloat(jTextField6.getText());
		}
		//w component
		if(e.getDocument() == jTextField7.getDocument()) {
			temp_w[0] = Float.parseFloat(jTextField7.getText());
		}
		if(e.getDocument() == jTextField8.getDocument()) {
			temp_w[1] = Float.parseFloat(jTextField8.getText());
		}
		if(e.getDocument() == jTextField9.getDocument()) {
			temp_w[2] = Float.parseFloat(jTextField9.getText());
		}
		//position component
		if(e.getDocument() == jTextField10.getDocument()) {
			temp_Q[0] = Float.parseFloat(jTextField10.getText());
		}
		if(e.getDocument() == jTextField11.getDocument()) {
			temp_Q[1] = Float.parseFloat(jTextField11.getText());
		}
		if(e.getDocument() == jTextField12.getDocument()) {
			temp_Q[2] = Float.parseFloat(jTextField12.getText());
		}
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		//u component
		if(e.getDocument() == jTextField1.getDocument()) {
			temp_u[0] = Float.parseFloat(jTextField1.getText());
		}
		if(e.getDocument() == jTextField2.getDocument()) {
			temp_u[1] = Float.parseFloat(jTextField2.getText());
		}
		if(e.getDocument() == jTextField3.getDocument()) {
			temp_u[2] = Float.parseFloat(jTextField3.getText());
		}
		//v component
		if(e.getDocument() == jTextField4.getDocument()) {
			temp_v[0] = Float.parseFloat(jTextField4.getText());
		}
		if(e.getDocument() == jTextField5.getDocument()) {
			temp_v[1] = Float.parseFloat(jTextField5.getText());
		}
		if(e.getDocument() == jTextField6.getDocument()) {
			temp_v[2] = Float.parseFloat(jTextField6.getText());
		}
		//w component
		if(e.getDocument() == jTextField7.getDocument()) {
			temp_w[0] = Float.parseFloat(jTextField7.getText());
		}
		if(e.getDocument() == jTextField8.getDocument()) {
			temp_w[1] = Float.parseFloat(jTextField8.getText());
		}
		if(e.getDocument() == jTextField9.getDocument()) {
			temp_w[2] = Float.parseFloat(jTextField9.getText());
		}
		//position component
		if(e.getDocument() == jTextField10.getDocument()) {
			temp_Q[0] = Float.parseFloat(jTextField10.getText());
		}
		if(e.getDocument() == jTextField11.getDocument()) {
			temp_Q[1] = Float.parseFloat(jTextField11.getText());
		}
		if(e.getDocument() == jTextField12.getDocument()) {
			temp_Q[2] = Float.parseFloat(jTextField12.getText());
		}
	}

	private void RadianToDegree() {
		temp_theta1 = temp_theta1 * 180 / Math.PI;
		temp_theta2 = temp_theta2 * 180 / Math.PI;
		temp_theta3 = temp_theta3 * 180 / Math.PI;
		temp_theta4 = temp_theta4 * 180 / Math.PI;
		temp_theta5 = temp_theta5 * 180 / Math.PI;
		temp_theta6 = temp_theta6 * 180 / Math.PI;
	}
	
	public void initSet() {
		temp_u[0] = Float.parseFloat(jTextField1.getText());
		temp_u[1] = Float.parseFloat(jTextField2.getText());
		temp_u[2] = Float.parseFloat(jTextField3.getText());
		
		temp_v[0] = Float.parseFloat(jTextField4.getText());
		temp_v[1] = Float.parseFloat(jTextField5.getText());
		temp_v[2] = Float.parseFloat(jTextField6.getText());
		
		temp_w[0] = Float.parseFloat(jTextField7.getText());
		temp_w[1] = Float.parseFloat(jTextField8.getText());
		temp_w[2] = Float.parseFloat(jTextField9.getText());
		
		temp_Q[0] = Float.parseFloat(jTextField10.getText());
		temp_Q[1] = Float.parseFloat(jTextField11.getText());
		temp_Q[2] = Float.parseFloat(jTextField12.getText());
		
		temp_pos[0] = (float) (temp_Q[0] - 232.5 * temp_w[0]);
		temp_pos[1] = (float) (temp_Q[1] - 232.5 * temp_w[1]);
		temp_pos[2] = (float) (temp_Q[2] - 232.5 * temp_w[2] - 400);
	}
	
	//做動畫用，把各角度細分100等分
	private void AnimationSet(boolean Flag) {
		if(Flag) {
		//Flag為真，將初始角度另存，用以相減u2...之參數的新角度
			temp_theta1_1 = temp_theta1;
			temp_theta2_1 = temp_theta2;
			temp_theta3_1 = temp_theta3;
			temp_theta4_1 = temp_theta4;
			temp_theta5_1 = temp_theta5;
			temp_theta6_1 = temp_theta6;
		} else {
		//計算做動畫初始角度
			theta1 = temp_theta1;
			theta2 = temp_theta2;
			theta3 = temp_theta3;
			theta4 = temp_theta4;
			theta5 = temp_theta5;
			theta6 = temp_theta6;
		}
	}

	private void thetaSample(int t_Span) {
		temp_theta1 = temp_theta1 / t_Span;
		temp_theta2 = temp_theta2 / t_Span;
		temp_theta3 = temp_theta3 / t_Span;
		temp_theta4 = temp_theta4 / t_Span;
		temp_theta5 = temp_theta5 / t_Span;
		temp_theta6 = temp_theta6 / t_Span;
	}
	
	private void ThetaStep() {
		theta1 += temp_theta1;
		theta2 += temp_theta2;
		theta3 += temp_theta3;
		theta4 += temp_theta4;
		theta5 += temp_theta5;
		theta6 += temp_theta6;
	}
	
	private void SubtractTheta() {
		temp_theta1 -= temp_theta1_1;
		temp_theta2 -= temp_theta2_1;
		temp_theta3 -= temp_theta3_1;
		temp_theta4 -= temp_theta4_1;
		temp_theta5 -= temp_theta5_1;
		temp_theta6 -= temp_theta6_1;
	}
	
	//透過不同的u, v, w, pos的輸入將設為全域變數的各個角度計算出來
	private void ThetaCalculate(float[] u, float[] v, float[] w, float[] pos) {
		inverseCal = new Inverse(u, v, w, pos);
		temp_theta1 = inverseCal.getTheta1();
		temp_theta5 = inverseCal.getTheta5(temp_theta1);
		theta234 = inverseCal.getTheta234(temp_theta1, temp_theta5);
		temp_theta3 = inverseCal.getTheta3(temp_theta1, theta234, 300, 250, 175);
		temp_theta2 = inverseCal.getTheta2(temp_theta1, temp_theta3, theta234, 300, 250, 175);
		temp_theta4 = inverseCal.getTheta4(temp_theta2, temp_theta3, theta234);
		temp_theta6 = inverseCal.getTheta6(temp_theta1, temp_theta5, theta234);
		RadianToDegree();
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		// TODO Auto-generated method stub
		if(arg0.getSource() == variableButton) {
			new VariableDialog(u1, u2, v1, v2, w1, w2, Q1, Q2);
		}
		
		if(arg0.getSource() == timer) {
			ThetaStep();
			pane2.repaint();
			t_span--;      //t_span預設100每經過0.01秒減一
			//若t_span = 1, 且stateFlag為真，即進入第二段動畫(從第一位置移動到第二位置)
			if(t_span == 1) {
				if(stateFlag == true) {
					t_span = 50;
					ThetaCalculate(u2, v2, w2, pos2);
					thetaSample(50);
					SubtractTheta();
					AnimationSet(false);
					stateFlag = false;
					cuboidFlag= false;
					timer.start();
				}
				
				if(t_span == 1) {
					t_span = 50;
					timer.stop();
				}
			}
			
		}
		if(arg0.getSource() == animateButton) {
		/*
		 * AnimateFlag為真，從原點到第一位置開始抓取長方體在移動到第二位置
		 * 若為假，表示不是一開始的狀態，故不必從原點開始出發
		 */
			if(AnimateFlag) {
				ThetaCalculate(u1, v1, w1, pos1);
				thetaSample(50);
				AnimationSet(false);
				AnimationSet(true);
				stateFlag = true;
				cuboidFlag = true;
				LocationFlag = true;
				timer.start();
			} else {
				ThetaCalculate(u1, v1, w1, pos1);
				thetaSample(50);
				AnimationSet(true);
				ThetaCalculate(u2, v2, w2, pos2);
				thetaSample(50);
				SubtractTheta();
				AnimationSet(false);
				stateFlag = false;
				cuboidFlag= false;
				timer.start();
			}

		}
		if(arg0.getSource() == renewButton) {
		/*
		 * LocationFlag為真，將u2...的值推給u1...等變數
		 * 若為假，及輸入的數字存到temp_u...直接存到u1...等變數
		 */
			temp_pos[0] = (float) (temp_Q[0] - 232.5 * temp_w[0]);
			temp_pos[1] = (float) (temp_Q[1] - 232.5 * temp_w[1]);
			temp_pos[2] = (float) (temp_Q[2] - 232.5 * temp_w[2] - 400);
		
			if(LocationFlag) {
				for(int i=0; i<3; i++) {
					u1[i] = u2[i];
					v1[i] = v2[i];
					w1[i] = w2[i];
					Q1[i] = Q2[i];
					pos1[i] = pos2[i];
				}
			} else {
				for(int i=0; i<3; i++) {
					u1[i] = temp_u[i];
					v1[i] = temp_v[i];
					w1[i] = temp_w[i];
					Q1[i] = temp_Q[i];
					pos1[i] = temp_pos[i];
				}
			}
			//正常狀況每次輸入皆將temp_u...存到u2...等變數
			for(int i=0; i<3; i++) {
				u2[i] = temp_u[i];
				v2[i] = temp_v[i];
				w2[i] = temp_w[i];
				Q2[i] = temp_Q[i];
				pos2[i] = temp_pos[i];
			}
			LocationFlag = true;
			cuboidFlag = true;
			signalFlag = true;
			
			//尚未設定第三個位置時，動畫仍從原點開始
			index++;
			if(index > 2) {
				AnimateFlag = false;
				index = 3;
			}
			/////////////////////////////////////
			pane2.repaint();
			animateButton.setEnabled(true);
		}
	}
}

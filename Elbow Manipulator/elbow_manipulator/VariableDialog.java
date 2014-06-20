package elbow_manipulator;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class VariableDialog extends JFrame {

	/**
	 * 秀出主Frame裏面的變數
	 */
	private static final long serialVersionUID = 1L;

	private JPanel jPanel1;
	private JLabel jLabel3;
	private JLabel jLabel4;
	private JLabel jLabel5;
	private JLabel jLabel23;
	private JLabel jLabel22;
	private JLabel jLabel21;
	private JLabel jLabel32;
	private JLabel jLabel31;
	private JLabel jLabel30;
	private JLabel jLabel29;
	private JLabel jLabel28;
	private JLabel jLabel27;
	private JLabel jLabel26;
	private JLabel jLabel25;
	private JLabel jLabel24;
	private JLabel jLabel20;
	private JLabel jLabel19;
	private JLabel jLabel18;
	private JLabel jLabel17;
	private JLabel jLabel16;
	private JLabel jLabel15;
	private JLabel jLabel14;
	private JLabel jLabel13;
	private JLabel jLabel12;
	private JLabel jLabel11;
	private JLabel jLabel10;
	private JLabel jLabel9;
	private JLabel jLabel8;
	private JLabel jLabel7;
	private JLabel jLabel6;
	private JLabel jLabel2;
	private JLabel jLabel1;
	private JPanel jPanel2;
	private float[] u1, u2, v1, v2, w1, w2, Q1, Q2;

	public VariableDialog(float[] u1, float[] u2, float[] v1, float[] v2, 
						  float[] w1, float[] w2, float[] Q1, float[] Q2) {
		// TODO Auto-generated constructor stub
		this.u1 = u1;
		this.u2 = u2;
		this.v1 = v1;
		this.v2 = v2;
		this.w1 = w1; 
		this.w2 = w2;
		this.Q1 = Q1;
		this.Q2 = Q2;
		initGUI();
	}

	private void initGUI() {
		setSize(320, 300);
		setTitle("Variable");
		setVisible(true);
		setLocation(165, 90);
		getContentPane().setLayout(null);
		jPanel1 = new JPanel();
		jPanel1.setLayout(null);
		getContentPane().add(jPanel1);
		jPanel1.setBounds(0, 0, 300, 120);
		jPanel1.setBorder(BorderFactory.createTitledBorder("First position"));
		{
			jLabel1 = new JLabel();
			jPanel1.add(jLabel1);
			jLabel1.setText("u1 axis:");
			jLabel1.setBounds(15, 20, 65, 20);
			jLabel1.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel2 = new JLabel();
			jPanel1.add(jLabel2);
			jLabel2.setText("v1 axis:");
			jLabel2.setBounds(15, 40, 65, 20);
			jLabel2.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel3 = new JLabel();
			jPanel1.add(jLabel3);
			jLabel3.setText("w1 axis:");
			jLabel3.setBounds(15, 60, 65, 20);
			jLabel3.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel4 = new JLabel();
			jPanel1.add(jLabel4);
			jLabel4.setText("Position 1:");
			jLabel4.setBounds(15, 80, 65, 20);
			jLabel4.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel9 = new JLabel("" + u1[0]);
			jPanel1.add(jLabel9);
			jLabel9.setBounds(95, 20, 65, 20);
			jLabel9.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel10 = new JLabel("" + v1[0]);
			jPanel1.add(jLabel10);
			jLabel10.setBounds(95, 40, 65, 20);
			jLabel10.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel11 = new JLabel("" + w1[0]);
			jPanel1.add(jLabel11);
			jLabel11.setBounds(95, 60, 65, 20);
			jLabel11.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel12 = new JLabel("" + Q1[0]);
			jPanel1.add(jLabel12);
			jLabel12.setBounds(95, 80, 65, 20);
			jLabel12.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel13 = new JLabel("" + u1[1]);
			jPanel1.add(jLabel13);
			jLabel13.setBounds(165, 20, 65, 20);
			jLabel13.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel14 = new JLabel("" + v1[1]);
			jPanel1.add(jLabel14);
			jLabel14.setBounds(165, 40, 65, 20);
			jLabel14.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel15 = new JLabel("" + w1[1]);
			jPanel1.add(jLabel15);
			jLabel15.setBounds(165, 60, 65, 20);
			jLabel15.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel16 = new JLabel("" + Q1[1]);
			jPanel1.add(jLabel16);
			jLabel16.setBounds(165, 80, 65, 20);
			jLabel16.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel17 = new JLabel("" + u1[2]);
			jPanel1.add(jLabel17);
			jLabel17.setBounds(235, 20, 65, 20);
			jLabel17.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel18 = new JLabel("" + v1[2]);
			jPanel1.add(jLabel18);
			jLabel18.setBounds(235, 40, 65, 20);
			jLabel18.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel19 = new JLabel("" + w1[2]);
			jPanel1.add(jLabel19);
			jLabel19.setBounds(235, 60, 65, 20);
			jLabel19.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel20 = new JLabel("" + Q1[2]);
			jPanel1.add(jLabel20);
			jLabel20.setBounds(235, 80, 65, 20);
			jLabel20.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		jPanel2 = new JPanel();
		jPanel2.setLayout(null);
		jPanel2.setBounds(0, 120, 300, 120);
		getContentPane().add(jPanel2);
		jPanel2.setBorder(BorderFactory.createTitledBorder("Secend position"));
		{
			jLabel5 = new JLabel();
			jPanel2.add(jLabel5);
			jLabel5.setText("u2 axis:");
			jLabel5.setBounds(15, 20, 65, 20);
			jLabel5.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel6 = new JLabel();
			jPanel2.add(jLabel6);
			jLabel6.setText("v2 axis:");
			jLabel6.setBounds(15, 40, 65, 20);
			jLabel6.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel7 = new JLabel();
			jPanel2.add(jLabel7);
			jLabel7.setText("w2 axis:");
			jLabel7.setBounds(15, 60, 65, 20);
			jLabel7.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel8 = new JLabel();
			jPanel2.add(jLabel8);
			jLabel8.setText("Position 2:");
			jLabel8.setBounds(15, 80, 65, 20);
			jLabel8.setFont(new java.awt.Font("Times New Roman", 1, 14));
		}
		{
			jLabel21 = new JLabel("" + u2[0]);
			jPanel2.add(jLabel21);
			jLabel21.setBounds(95, 20, 65, 20);
			jLabel21.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel22 = new JLabel("" + v2[0]);
			jPanel2.add(jLabel22);
			jLabel22.setBounds(95, 40, 65, 20);
			jLabel22.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel23 = new JLabel("" + w2[0]);
			jPanel2.add(jLabel23);
			jLabel23.setBounds(95, 60, 65, 20);
			jLabel23.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel24 = new JLabel("" + Q2[0]);
			jPanel2.add(jLabel24);
			jLabel24.setBounds(95, 80, 65, 20);
			jLabel24.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel25 = new JLabel("" + u2[1]);
			jPanel2.add(jLabel25);
			jLabel25.setBounds(165, 20, 65, 20);
			jLabel25.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel26 = new JLabel("" + v2[1]);
			jPanel2.add(jLabel26);
			jLabel26.setBounds(165, 40, 65, 20);
			jLabel26.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel27 = new JLabel("" + w2[1]);
			jPanel2.add(jLabel27);
			jLabel27.setBounds(165, 60, 65, 20);
			jLabel27.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel28 = new JLabel("" + Q2[1]);
			jPanel2.add(jLabel28);
			jLabel28.setBounds(165, 80, 65, 20);
			jLabel28.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel29 = new JLabel("" + u2[2]);
			jPanel2.add(jLabel29);
			jLabel29.setBounds(235, 20, 65, 20);
			jLabel29.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel30 = new JLabel("" + v2[2]);
			jPanel2.add(jLabel30);
			jLabel30.setBounds(235, 40, 65, 20);
			jLabel30.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel31 = new JLabel("" + w2[2]);
			jPanel2.add(jLabel31);
			jLabel31.setBounds(235, 60, 65, 20);
			jLabel31.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
		{
			jLabel32 = new JLabel("" + Q2[2]);
			jPanel2.add(jLabel32);
			jLabel32.setBounds(235, 80, 65, 20);
			jLabel32.setFont(new java.awt.Font("Times New Roman", 0, 14));
		}
	}

}

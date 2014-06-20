package elbow_manipulator;

public class Inverse {

	@SuppressWarnings("unused")
	private float[] u, v, w, pos;
	
	public Inverse() {
		// TODO Auto-generated constructor stub
		
	}
	
	public Inverse(float[] u, float[] v, float[] w, float[] pos) {
		this.u = u;
		this.v = v;
		this.w = w;
		this.pos = pos;
	}
	
	public double getTheta1() {
		return Math.atan(pos[1] / pos[0]);
	}
	
	public double getTheta5(double theta1) {
		double temp = -w[0] * Math.sin(theta1) + w[1] * Math.cos(theta1);
			return Math.asin(temp);

	}
	
	public double getTheta234(double theta1, double theta5) {
		return Math.atan2(w[2] / Math.cos(theta5), (w[0] * Math.cos(theta1) + w[1] * Math.sin(theta1) / Math.cos(theta5)));
	}
	
	public double getTheta3(double theta1, double theta234, int a2, int a3, int a4) {
		double k1 = pos[0] * Math.cos(theta1) + pos[1] * Math.sin(theta1) - a4 * Math.cos(theta234);
		double k2 = pos[2] - a4 * Math.sin(theta234);
		return Math.acos((k1 * k1 + k2 * k2 - a2 * a2 - a3 * a3) / (2 * a2 * a3));
	}
	
	public double getTheta2(double theta1, double theta3, double theta234, int a2, int a3, int a4) {
		double k1 = pos[0] * Math.cos(theta1) + pos[1] * Math.sin(theta1) - a4 * Math.cos(theta234);
		double k2 = pos[2] - a4 * Math.sin(theta234);
		double k3 = a3 * Math.cos(theta3) + a2;
		double k4 = a3 * Math.sin(theta3);
		double c2 = (k1 * k3 + k2 * k4) / (k3 * k3 + k4 * k4);
		double s2 = (k1 * k4 - k2 * k3) / (-k4 * k4 - k3 * k3);
		return Math.atan2(s2, c2);
	}
	
	public double getTheta4(double theta2, double theta3, double theta234) {
		return theta234 - theta2 - theta3;
	}
	
	public double getTheta6(double theta1, double theta5, double theta234) {
		double s6 = Math.sin(theta5) * (u[0] * Math.cos(theta1) * Math.cos(theta234) + 
										u[1] * Math.sin(theta1) * Math.sin(theta234) + 
										u[2] * Math.sin(theta234)) 
				  - Math.cos(theta5) * (-u[0] * Math.sin(theta1) + u[1] * Math.cos(theta1));
		double c6 = -u[0] * Math.cos(theta1) * Math.sin(theta234) - u[1] * Math.sin(theta1) * Math.sin(theta234)
				   + u[2] * Math.cos(theta234);
		return Math.atan2(s6, c6);
	}
}

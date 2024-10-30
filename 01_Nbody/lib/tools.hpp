#ifdef TOOLS_HPP
#define TOOLS_HPP

class tools{
public:
      static std::vector<double> calc_accelaration(std::vector<Body> bodies, Body current_body)
      static std::vector<double> calc_jerk(std::vector<Body> bodies, Body current_body)
private:
    const static double G = 6.67430e-11;
};

#endif // TOOLS_HPP
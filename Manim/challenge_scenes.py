from manim import *
import os

class MovingCameraOnGraph(MovingCameraScene):
    def construct(self):
        self.camera.frame.save_state()

        ax = Axes(x_range=[-1, 10], y_range=[-1, 10])
        graph = ax.plot(lambda x: np.sin(x), color=WHITE, x_range=[0, 2 * PI])

        dot_1 = Dot(ax.i2gp(graph.t_min, graph))
        dot_2 = Dot(ax.i2gp(graph.t_max, graph))
        self.add(ax)#, dot_1, dot_2)

        self.play(self.camera.frame.animate.scale(0.5).move_to(dot_1))
        self.play(self.camera.frame.animate.move_to(dot_2))
        self.play(Restore(self.camera.frame))
        self.wait()

        #ax_1.to_corner(UL)
        #ax_2.to_corner(UR)
        #ax_3.to_edge(DOWN)

class Formula(Scene):
    def construct(self):
        t = MathTex(r"\int_a^b f'(x) dx = f(b)- f(a)")
        self.add(t)

class Intro(Scene):
    def construct(self):
        class_name = Text("TE3001B Robotics Foundation 2024").move_to(UP)
        TEC_logo_path = "tecnologico-de-monterrey-black.svg"
        MCR_logo_path = "MCR.svg"
        JC = Text("Juan Carlos Hernández Ríos | A01740821").scale(0.5).move_to(0.5*DOWN)
        Dan = Text("Daniel Noé Salinas Sánchez | A01704062").scale(0.5).move_to(1*DOWN)
        Emi = Text("José Emiliano Flores Martínez | A00833160").scale(0.5).move_to(1.5*DOWN)
        Dav = Text("David Israel Vázquez Leal | A00833121").scale(0.5).move_to(2*DOWN)
        Chap = Text("Alexis Chapa Romero | A00832711").scale(0.5).move_to(2.5*DOWN)
        Pac = Text("Francisco Salas Porras | A01177893").scale(0.5).move_to(3*DOWN)

        TEC_logo = SVGMobject(TEC_logo_path,width=10,fill_color="#ffffff")
        MCR_logo = SVGMobject(MCR_logo_path,width=10).scale(0.6)

        self.play(DrawBorderThenFill(TEC_logo))
        self.play(TEC_logo.animate.scale(0.3).move_to(3*UP + 5*LEFT))
        self.wait(0.2)
        self.play(DrawBorderThenFill(MCR_logo))
        self.play(MCR_logo.animate.scale(0.2).move_to(3*UP + 6*RIGHT))
        self.wait(0.2)
        self.play(FadeIn(class_name, shift=UP))
        self.wait(0.2)
        self.play(FadeIn(JC), FadeIn(Dan), FadeIn(Emi), FadeIn(Dav), FadeIn(Chap), FadeIn(Pac))
        self.wait(0.2)
        self.play(FadeOut(TEC_logo, shift=UP), 
                  FadeOut(MCR_logo, shift=UP),
                  FadeOut(class_name, shift=UP),
                    FadeOut(JC, shift=UP),
                    FadeOut(Dan, shift=UP),
                    FadeOut(Emi, shift=UP),
                    FadeOut(Dav, shift=UP),
                    FadeOut(Chap, shift=UP),
                    FadeOut(Pac, shift=UP)
                  )
        self.wait(0.2)

        #self.play(Create(MCR_logo))
        #self.wait()
        #self.play(Uncreate(MCR_logo))
        #self.wait()

class motorAnalysis(MovingCameraScene):
    def construct(self):
        
        ## Define objects

        title = Text("Motor Analysis").move_to(3.25*UP + 4*RIGHT)

        xRange = [-500, 11000, 1000]
        yRange = [-0.5, 6, 0.5]
        ax = Axes(x_range=xRange, 
                  y_range=yRange, 
                  tips=False,
                  axis_config={"include_numbers": True},
                  ).move_to(0.5*DOWN)
        ax_labels = ax.get_axis_labels(
            Tex(r"$t$ (ms)").scale(0.7), Tex(r"$\omega$ (rad/s)").scale(0.7)
        )
        axis = VGroup(ax, ax_labels)
        
        coords = self.return_coords_from_csv("motor_behaviour")
        x_vals = []
        y_vals = []
        for coord in coords:
            x_vals.append(coord[0])
            y_vals.append(coord[1])

        line_graph = ax.plot_line_graph(
            x_values = x_vals,
            y_values = y_vals,
            line_color = GOLD_E,
            add_vertex_dots=False,
            vertex_dot_style = dict(stroke_width=3,  fill_opacity=0.0),
            stroke_width = 4,
        )

        line_graph_2 = ax.plot_line_graph(
            x_values = x_vals,
            y_values = y_vals,
            line_color = GOLD_E,
            add_vertex_dots=True,
            vertex_dot_style = dict(stroke_width=3,  fill_opacity=0.0),
            stroke_width = 4,
        )

        ss_line = ax.plot(lambda x: 5.2, x_range=[0,10200] , color=YELLOW_B)
        ss_label = ax.get_graph_label(ss_line, "5.2", x_val=10200, direction=RIGHT)
        ss_label_2 = ax.get_graph_label(ss_line, Tex(r"$\omega_{ss}$"), x_val=10200, direction=RIGHT)
        
        prim_x = x_vals[3]
        prim_y = y_vals[3]
        prim_dot = LabeledDot(Tex(r"$\omega'$", color=BLACK).scale(0.3), 
                            point=ax.coords_to_point(prim_x, prim_y), 
                            radius=0.125, 
                            fill_color=GREEN)
        prim_values = Matrix([[prim_x, prim_y]]).scale(0.5).next_to(prim_dot, RIGHT + DOWN)
        prim_show = VGroup(prim_dot, prim_values)
        prim_pos = Dot(ax.coords_to_point(1500, 3), radius=0.0, color=WHITE)

        frml_size = 0.9
        frml1_pos = Dot(ax.coords_to_point(7000, 3.1), radius=0.0, color=WHITE)
        frml2_pos = Dot(ax.coords_to_point(7000, 2.1), radius=0.0, color=WHITE)
        frml_pos = Dot(ax.coords_to_point(7000, 2.6), radius=0.0, color=WHITE)
        frml1 = Tex(r"$\omega(t)=\omega_{ss}(1-e^{-\tau t})$").scale(frml_size).move_to(frml1_pos)
        frml1_1 = Tex(r"$\omega'=\omega_{ss}(1-e^{-\tau t'})$").scale(frml_size).move_to(frml1_pos)
        frml1_2 = Tex(r"$\frac{\omega'}{\omega_{ss}}=1-e^{-\tau t'}$").scale(frml_size).move_to(frml1_pos)
        frml1_3 = Tex(r"$1-\frac{\omega'}{\omega_{ss}}=e^{-\tau t'}$").scale(frml_size).move_to(frml1_pos)
        frml1_4 = Tex(r"$\ln\left(1-\frac{\omega'}{\omega_{ss}}\right)=-\tau t'$").scale(frml_size).move_to(frml1_pos)
        frml1_5 = Tex(r"$\tau=-\frac{\ln\left(1-\frac{\omega'}{\omega_{ss}}\right)}{t'}$").scale(frml_size).move_to(frml1_pos)
        frml1_6 = Tex(r"$\tau = -\frac{\ln\left(1-\frac{(3.2)}{(5.2))}\right)}{(300)}$").scale(frml_size).move_to(frml1_pos)
        frml1_7 = Tex(r"$\tau = 3.185 \cdot 10^{-3}$").scale(frml_size).move_to(frml1_pos)
        frml2 = Tex(r"$\omega_{ss} = \frac{V_o k}{\tau}$").scale(frml_size).move_to(frml2_pos)
        frml2_1 = Tex(r"$\omega_{ss} \tau = V_o k$").scale(frml_size).move_to(frml2_pos)
        frml2_2 = Tex(r"$k = \frac{\omega_{ss} \tau}{V_o}$").scale(frml_size).move_to(frml2_pos)
        frml2_3 = Tex(r"$k = \frac{(5.2) (3.185)}{(6)}$").scale(frml_size).move_to(frml2_pos)
        frml2_4 = Tex(r"$k = 2.760\overline{3}$").scale(frml_size).move_to(frml2_pos)

        ## Scene
        
        ## Show title
        self.camera.frame.save_state()
        self.play(FadeIn(title, shift=UP), FadeIn(axis, shift=UP))
        self.play(FadeIn(line_graph_2))
        ## Show graph
        self.wait()
        self.play(FadeOut(line_graph_2), FadeIn(line_graph))
        self.wait()
        self.play(FadeIn(ss_line), FadeIn(ss_label_2))
        self.wait()
        self.play(FadeOut(ss_label_2), FadeIn(ss_label))
        self.wait()
        self.play(FadeOut(ss_line), FadeOut(ss_label))
        self.play(FadeIn(prim_show))
        self.play(self.camera.frame.animate.scale(0.3).move_to(prim_pos))
        self.wait()
        ## Show formulas
        self.add(frml1_pos, frml_pos)
        self.play(self.camera.frame.animate.scale(1.5).move_to(frml1_pos))
        self.play(Write(frml1))
        self.wait()
        self.play(ReplacementTransform(frml1, frml1_1))
        self.wait()
        self.play(ReplacementTransform(frml1_1, frml1_2))
        self.wait()
        self.play(ReplacementTransform(frml1_2, frml1_3))
        self.wait()
        self.play(ReplacementTransform(frml1_3, frml1_4))
        self.wait()
        self.play(ReplacementTransform(frml1_4, frml1_5))
        self.wait()
        self.play(ReplacementTransform(frml1_5, frml1_6))
        self.wait()
        self.play(ReplacementTransform(frml1_6, frml1_7))
        self.wait()
        self.play(self.camera.frame.animate.move_to(frml_pos))
        self.play(Write(frml2))
        self.wait()
        self.play(ReplacementTransform(frml2, frml2_1))
        self.wait()
        self.play(ReplacementTransform(frml2_1, frml2_2))
        self.wait()
        self.play(ReplacementTransform(frml2_2, frml2_3))
        self.wait()
        self.play(ReplacementTransform(frml2_3, frml2_4))
        self.wait()
        self.play(Restore(self.camera.frame))
        self.wait()
        ## End scene
        self.play(FadeOut(title, shift=UP), 
                  FadeOut(axis, shift=UP), 
                  FadeOut(line_graph, shift=UP), 
                  FadeOut(prim_show, shift=UP), 
                  FadeOut(frml1_pos, shift=UP), 
                  FadeOut(frml_pos, shift=UP),
                  FadeOut(frml1_7, shift=UP),
                  FadeOut(frml2_4, shift=UP))
        self.wait()

        
    def return_coords_from_csv(self,file_name):
        import csv
        coords = []
        with open(f'{file_name}.csv', 'r') as csvFile:
            reader = csv.reader(csvFile)
            for row in reader:
                x,y = row
                x = float(x) - 1000
                y = float(y)
                coords.append([x,y])
        csvFile.close()
        return coords

class Ending(Scene):
    def construct(self):
        thanks = Text("Thanks for watching!").scale(1.5)
        animate = Text("Animated using:").move_to(1.5*UP)
        banner = ManimBanner().move_to(DOWN)

        self.play(FadeIn(thanks))
        self.play(thanks.animate.scale(0.4).move_to(2*UP))
        self.play(FadeIn(animate))
        self.wait(0.1)
        self.play(banner.create())
        self.play(banner.expand())
        self.wait()
        self.play(
            FadeOut(thanks),
            FadeOut(animate),
            Unwrite(banner)
        )
        self.wait(2)
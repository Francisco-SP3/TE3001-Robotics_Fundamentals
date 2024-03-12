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
        class_name = Text("TE3001B Robotics Foundation 2024")
        TEC_logo_path = "tecnologico-de-monterrey-black.svg"
        MCR_logo_path = "MCR.png"

        TEC_logo = SVGMobject(TEC_logo_path,width=10,fill_color="#ffffff")
        MCR_logo = ImageMobject(MCR_logo_path)

        #self.play(AddTextLetterByLetter(class_name))
        self.play(DrawBorderThenFill(TEC_logo))
        self.wait()
        #self.play(RemoveTextLetterByLetter(class_name))
        self.play(FadeOut(TEC_logo))
        self.wait()

        #self.play(Create(MCR_logo))
        #self.wait()
        #self.play(Uncreate(MCR_logo))
        #self.wait()

class motorAnalysis(MovingCameraScene):
    def construct(self):
        title = Text("Motor Analysis").move_to(3.25*UP + 4*LEFT)
        OoB = Dot(10*UP, radius=0.0)
        xRange = [-100, 12600, 100]
        yRange = [-0.5, 5.5, 0.5]
        coords = self.return_coords_from_csv("motor_behaviour")
        ax = Axes(x_range=xRange, y_range=yRange).move_to(0.5*DOWN)
        
        self.camera.frame.save_state()
        self.add(OoB)
        self.play(self.camera.frame.animate.move_to(OoB))
        self.add(title)
        self.add(ax)
        for coord in coords:
            dot = Dot(ax.c2p(coord[0],coord[1]), color=WHITE)
            self.add(dot)
        self.play(Restore(self.camera.frame))
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
        self.play(ApplyMethod(thanks.move_to, 2.5*UP))
        self.play(FadeIn(animate))
        self.wait(0.1)
        self.play(banner.create())
        self.play(banner.expand())
        self.wait()
        self.play(Succession(
            FadeOut(thanks),
            FadeOut(animate),
            Unwrite(banner)
        ))
        self.wait(2)
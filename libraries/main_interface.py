from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.spinner import Spinner
from kivy.uix.filechooser import FileChooserController

from parallel_functions import call_nmroots, finding_roots
import numpy as np

def saveInfo(l):
    l[-1].clear_widgets()
    l[-1].add_widget(Label(text="Working...", size_hint = (.2, None), height =30))
    if l[0] == 0:
        #option, a.text, b.text, prec.text, cores.text, name.text, parent2
        np.savetxt("../%s.txt"%l[-2],np.array([finding_roots(float(l[1]), float(l[2]), l[0], float(l[3]), 0.001, int(l[4]))]))
    elif l[0] == 1:
        np.savetxt("../%s.txt"%l[-2],finding_roots(float(l[1]), float(l[2]), l[0], float(l[3]), float(l[4]), int(l[5])))
    else:
        #a.text, b.text, prec.text, error.text, cores.text
        np.savetxt("../%s.txt"%l[-2],call_nmroots(int(l[1]), int(l[2]), float(l[3]), float(l[4])))
    l[-1].add_widget(Label(text="Done! Saved in %s.txt"%l[-2], size_hint = (.2, None), height =30))

def new_layout(spinner, text, parent, parent2, vals):
    option = vals.index(text)
    parent.clear_widgets()
    goButton = Button(text = "Calculate")
    name = TextInput(text="result",multiline = False, size_hint = (.2, None), height =30)

    if option == 0 or option ==1:
        parent.add_widget(Label(text="a =", size_hint = (.2, None), height =30))
        a = TextInput(multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(a)

        parent.add_widget(Label(text="b =", size_hint = (.2, None), height =30))
        b = TextInput(multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(b)

        parent.add_widget(Label(text="prec (size of intervals to check existence of a root) =", size_hint = (.2, None), height =30))
        prec = TextInput(text="0.01",multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(prec)

        if option == 1:
            parent.add_widget(Label(text=" error (maximum error in the roots) =", size_hint = (.2, None), height =30))
            error = TextInput(text="0.001",multiline = False, size_hint = (.2, None), height =30)
            parent.add_widget(error)

        parent.add_widget(Label(text="cores (# of cores to be used) =", size_hint = (.2, None), height =30))
        cores = TextInput(text="1",multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(cores)
        if option == 0:
            goButton.bind(on_press =lambda something: saveInfo([option, a.text, b.text, prec.text, cores.text, name.text, parent2]))
        else:
            goButton.bind(on_press =lambda something: saveInfo([option, a.text, b.text, prec.text, error.text, cores.text, name.text, parent2]))


    else:
        parent.add_widget(Label(text="n =", size_hint = (.2, None), height =30))
        n = TextInput(multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(n)

        parent.add_widget(Label(text="m =", size_hint = (.2, None), height =30))
        m = TextInput(multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(m)

        parent.add_widget(Label(text="prec (size of intervals to check existence of a root) =", size_hint = (.2, None), height =30))
        prec = TextInput(text="0.01",multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(prec)

        parent.add_widget(Label(text=" error (maximum error in the roots) =", size_hint = (.2, None), height =30))
        error = TextInput(text="0.001",multiline = False, size_hint = (.2, None), height =30)
        parent.add_widget(error)

        goButton.bind(on_press =lambda something: saveInfo([option, n.text, m.text, prec.text, error.text, name.text, parent2]))

    parent.add_widget(Label(text="filename (to save the results) =", size_hint = (.2, None), height =30))
    parent.add_widget(name)

    parent.add_widget(Label())
    parent.add_widget(goButton)

class MainScreen(GridLayout):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)
        self.cols = 1
        self.add_widget(Label(text="This program has three functionalities, it can calculate the number of roots with \nimaginary  part in a given interval [a,b], show them explicitly with a given precision \nand calculate the list {a_n,...,a_m}, where a_i is the imaginary part of the i-th root.\nChoose the functionality below.", size_hint = (0.3, 0.3), width =40))

        vals = ('Number of roots with imaginary part in [a,b].', 'Calculate roots with imaginary part in [a,b].', 'Calculate {a_n, ..., a_m}.')

        spinner = Spinner(
        text='Choose clicking here',
        # available values
        values=vals,
        size_hint=(None, None),
        size=(350, 44))
        layout =  GridLayout(padding=10, cols =2)
        second_layout = GridLayout(padding=10, cols=1)
        spinner.bind(text=lambda instance, tex: new_layout(instance, tex, layout, second_layout, vals))

        self.add_widget(spinner)
        self.add_widget(layout)
        self.add_widget(second_layout)

class MyApp(App):
    def build(self):
        self.title = "Riemman Zeta Function Zeros"
        return MainScreen()
if __name__ == '__main__':
    MyApp().run()

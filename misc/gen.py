#!/usr/bin/python3

header = '''<interface>
    <object id="window" class="GtkWindow">
        <property name="visible">True</property>
        <property name="title">ms</property>
        <child>
            <object class="GtkGrid">
                <property name="visible">True</property>
                <child>
                    <object class="GtkGrid">
                        <property name="visible">True</property>
'''
footer = '''                    </object>
                    <packing>
                        <property name="left-attach">0</property>
                        <property name="top-attach">1</property>
                    </packing>
                </child>
                <child>
                    <object id="indicator" class="GtkLabel">
                        <property name="visible">True</property>
                    </object>
                    <packing>
                        <property name="left-attach">0</property>
                        <property name="top-attach">0</property>
                    </packing>
                </child>
            </object>
        </child>
    </object>
</interface>
'''

template = '''                        <child>
                            <object id="grid{}-{}" class="GtkButton">
                                <property name="visible">True</property>
                                <property name="width-request">50</property>
                                <property name="height-request">50</property>
                            </object>
                            <packing>
                                <property name="left-attach">{}</property>
                                <property name="top-attach">{}</property>
                            </packing>
                        </child>
'''
def main():
    with open("../ms-gtk/res/easy.ui", "w") as fout:
        fout.write(header)
        for i in range(8):
            for j in range(8):
                fout.write(template.format(i, j, j, i))
        fout.write(footer)
    with open("../ms-gtk/res/normal.ui", "w") as fout:
        fout.write(header)
        for i in range(16):
            for j in range(16):
                fout.write(template.format(i, j, j, i))
        fout.write(footer)
    with open("../ms-gtk/res/hard.ui", "w") as fout:
        fout.write(header)
        for i in range(16):
            for j in range(30):
                fout.write(template.format(i, j, j, i))
        fout.write(footer)
if __name__ == "__main__":
    main()
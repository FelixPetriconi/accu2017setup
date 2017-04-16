#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>

int main()
{
  using namespace nana;

  form fm;

  label lb{ fm };
  lb.caption("Welcome to ACCU 2017!");

  lb.bgcolor(colors::azure);

  place layout(fm);
  layout.div("vert<><<here>><>");
  layout["here"] << lb;
  layout.collocate();

  fm.show();

  exec();
}
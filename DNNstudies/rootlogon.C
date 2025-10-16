void rootlogon()
{
  // Load ATLAS style
  gROOT->ProcessLine(".L /home/john/atlas/RootUtils/AtlasStyle.C");
  gROOT->ProcessLine("SetAtlasStyle()");
}

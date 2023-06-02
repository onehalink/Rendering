// See https://aka.ms/new-console-template for more information
//Console.WriteLine("Hello, World!");



#region Helper
var IsUpperCase = (char code) =>
{
    return code >= 'A' && code <= 'Z';
};

var IsLowerCase = (char code) =>
{
    return code >= 'a' && code <= 'z';
};

var IsFunctionPointer = (string text) =>
{
    if ( text.Length <= 2 )
        return false;

    if ( text[0] != '\t' )
        return false;

    if ( !IsUpperCase(text[1]) && !IsLowerCase(text[1]) )
        return false;

    if ( !text.Contains("(*") )
        return false;

    return true;
};
#endregion


var CHeaderPath = @"C:\Users\Admin\Desktop\0508\Rendering\C\Engine\Source\Runtime\Asset\Asset.h";
var CSourcePath = CHeaderPath.Replace(".h", ".c");

var CHeader = CHeaderPath.Substring( CHeaderPath.LastIndexOf('\\') + 1 );


if ( File.Exists(CSourcePath) )
    return;


var lines = File.ReadAllLines(CHeaderPath);


var APISetName = "";
{
    var prefix = "extern ENGINE_API ";
    var suffix = ";";

    foreach (var line in lines)
        if ( line.StartsWith(prefix) )
            APISetName = line.Replace(prefix, "").Replace(suffix, "");

    Console.WriteLine( APISetName );
}


var FuntionPointers = new List<string>();
var Signatures      = new List<string>();

foreach (var line in lines)
{
    if ( !IsFunctionPointer(line) )
        continue;

    var Return = "";
    {
        var begin   = 1;
        var end     = line.IndexOf('(');

        Return = line.Substring(begin, end - begin);
    }

    var Name = "";
    {
        var begin   = line.IndexOf('(') + 2;
        var end     = line.IndexOf(')');

        Name = line.Substring(begin, end - begin);
    }

    var Arguments = "";
    {
        var begin   = line.LastIndexOf('(') + 1;
        var end     = line.LastIndexOf(')');

        Arguments = line.Substring(begin, end - begin);
    }


    var Definition = $"static {Return} {Name}({Arguments})" + "\n{\n\n}";


    Console.WriteLine("---");
    Console.WriteLine($"Return:     {Return}");
    Console.WriteLine($"Name:       {Name}");
    Console.WriteLine($"Arguments:  {Arguments}");
    Console.WriteLine($"Definition: {Definition}");


    FuntionPointers.Add(Name);
    Signatures.Add(Definition);
}


var sb = new System.Text.StringBuilder();

sb.AppendLine($"#include \"{CHeader}\"");
sb.AppendLine();
sb.AppendLine();
sb.AppendLine();

foreach(var signature in Signatures)
{
    sb.AppendLine(signature);
    sb.AppendLine();
}

sb.AppendLine();
sb.AppendLine($"{APISetName} = ");
sb.AppendLine("{");
foreach (var fp in FuntionPointers) sb.AppendLine($"\t{fp},");
sb.AppendLine("};");


File.WriteAllText( CSourcePath, sb.ToString() );
System.Diagnostics.Process.Start("notepad", CSourcePath);
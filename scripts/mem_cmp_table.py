import os
import sys
import datetime
from dataclasses import dataclass
from typing import List, Literal, Dict, Tuple, Optional

def read_memstat_files(directory_path="build/memstats"):
    """
    Reads all files in the specified directory and returns a list where
    each element is the contents of a file.
    
    Args:
        directory_path: Path to the directory containing the files
        
    Returns:
        A list of tuples (filename, contents) for each file
    """
    file_contents = []
    
    # Make sure the directory exists
    if not os.path.exists(directory_path) or not os.path.isdir(directory_path):
        print(f"Error: Directory '{directory_path}' does not exist or is not a directory")
        return []
    
    # Get all files in the directory
    try:
        files = [f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
    except Exception as e:
        print(f"Error accessing directory: {e}")
        return []
    
    # Read each file
    for filename in sorted(files):
        file_path = os.path.join(directory_path, filename)
        try:
            with open(file_path, 'r') as file:
                content = file.read()
                file_contents.append((filename, content))
                print(f"Read file: {filename}")
        except Exception as e:
            print(f"Error reading file {filename}: {e}")
    
    return file_contents

@dataclass
class SizeCommandOutput_C:
    """Represents the output of the 'size' command for an object file."""
    
    text: int
    """Size of the text (code) section in bytes"""
    
    data: int
    """Size of the initialized data section in bytes"""
    
    bss: int
    """Size of the uninitialized data (BSS) section in bytes"""
    
    dec: int
    """Total size in decimal (text + data + bss)"""
    
    hex: str
    """Total size in hexadecimal"""
    
    filename: str
    """Name of the object file"""
    
    library_path: Optional[str] = None
    """Path to the library containing the object file, if applicable"""
    
    @classmethod
    def from_size_output(cls, line: str) -> "SizeCommandOutput_C":
        """
        Parse a line from the 'size' command output into a SizeCommandOutput_C object.
        
        Args:
            line: A line from the output of the 'size' command
            
        Returns:
            A SizeCommandOutput_C object with parsed values
        """
        parts = line.strip().split()
        
        # Parse the filename and extract library path if present
        filename = parts[5]
        library_path = None
        
        if "(" in parts[5] and ")" in " ".join(parts[5:]):
            # Handle case where filename contains library path
            full_name = " ".join(parts[5:])
            filename_part = full_name.split(" (ex ")[0]
            library_path = full_name.split(" (ex ")[1].rstrip(")")
            filename = filename_part
        
        return cls(
            text=int(parts[0]),
            data=int(parts[1]),
            bss=int(parts[2]),
            dec=int(parts[3]),
            hex=parts[4],
            filename=filename,
            library_path=library_path
        )

# Define types for symbol categories
SymbolType = Literal['T', 't', 'B', 'b', 'R', 'r', 'D', 'd']

@dataclass
class NmSymbol_C:
    """Represents a symbol from the output of the nm command."""
    
    size: int
    """Size of the symbol in bytes"""
    
    type: SymbolType
    """Type of the symbol (T/t=text, B/b=BSS, R/r=read-only data, D/d=data)"""
    
    name: str
    """Name of the symbol"""
    
    @property
    def type_description(self) -> str:
        """Returns a human-readable description of the symbol type."""
        descriptions = {
            'T': 'Global code (text)',
            't': 'Local code (text)',
            'B': 'Global uninitialized data (BSS)',
            'b': 'Local uninitialized data (BSS)',
            'R': 'Global read-only data',
            'r': 'Local read-only data',
            'D': 'Global initialized data',
            'd': 'Local initialized data'
        }
        return descriptions.get(self.type, 'Unknown')
    
    @property
    def is_code(self) -> bool:
        """Returns True if the symbol is in the code/text section."""
        return self.type.upper() == 'T'
    
    @property
    def is_data(self) -> bool:
        """Returns True if the symbol is in a data section."""
        return self.type.upper() in ['B', 'R', 'D']
    
    @property
    def is_global(self) -> bool:
        """Returns True if the symbol is global (uppercase type)."""
        return self.type.isupper()
    
    @classmethod
    def from_nm_line(cls, line: str) -> Optional['NmSymbol_C']:
        """
        Parse a line from the nm command output into an NmSymbol_C object.
        
        Args:
            line: A line from the nm command output
            
        Returns:
            An NmSymbol_C object if the line contains a relevant symbol, None otherwise
        """
        parts = line.strip().split()
        if len(parts) < 3:
            return None
            
        # Check if this is a symbol we want to keep
        symbol_type = parts[2]
        if symbol_type not in "TtBbRrDd":
            return None
            
        # Check if this is a section name (starts with .)
        symbol_name = parts[3] if len(parts) > 3 else ""
        if symbol_name.startswith('.') or symbol_name.startswith('cov_'):
            return None
            
        # Extract the size (second column) in hex
        size_hex = parts[1]
        size = int(size_hex, 16)
            
        return cls(size=size, type=symbol_type, name=symbol_name)
    
    @classmethod
    def parse_nm_output(cls, output: str) -> List['NmSymbol_C']:
        """
        Parse the complete output of the nm command.
        
        Args:
            output: The complete output from the nm command
            
        Returns:
            A list of NmSymbol_C objects for all relevant symbols
        """
        symbols = []
        lines = output.strip().split('\n')
        
        for line in lines:
            if ':' in line and len(line.split(':')[0].split()) == 1:
                # This is an object file header line, skip it
                continue
                
            symbol = cls.from_nm_line(line)
            if symbol:
                symbols.append(symbol)
                
        return symbols

@dataclass
class MemStats_C:
    """Represents the complete memory statistics for a compiled object."""
    
    size_info: SizeCommandOutput_C
    """Size command output information"""
    
    symbols: List[NmSymbol_C]
    """List of symbols from nm command output"""
    
    @property
    def total_code_size(self) -> int:
        """Returns the total code size based on symbols."""
        return sum(symbol.size for symbol in self.symbols if symbol.is_code)
    
    @property
    def total_data_size(self) -> int:
        """Returns the total data size based on symbols."""
        return sum(symbol.size for symbol in self.symbols if symbol.is_data)
    
    @property
    def summary(self) -> dict:
        """Returns a summary dictionary of memory usage."""
        return {
            "filename": self.size_info.filename,
            "text_size": self.size_info.text,
            "data_size": self.size_info.data,
            "bss_size": self.size_info.bss,
            "total_size": self.size_info.dec,
            "symbol_count": len(self.symbols),
            "code_symbols": sum(1 for symbol in self.symbols if symbol.is_code),
            "data_symbols": sum(1 for symbol in self.symbols if symbol.is_data)
        }
    
    @classmethod
    def from_log_file(cls, content: str) -> "MemStats_C":
        """
        Parse the complete content of a memory statistics log file.
        
        Args:
            content: The complete content of the log file
            
        Returns:
            A MemStats_C object with parsed size information and symbols
        """
        # Split content into sections
        sections = content.strip().split("\n\n")
        
        # Parse size command output (first section)
        size_lines = sections[0].strip().split("\n")
        if len(size_lines) < 2:  # Need at least header and data line
            raise ValueError("Invalid size command output format")
        
        size_info = SizeCommandOutput_C.from_size_output(size_lines[1])
        
        # Parse nm command output (second section)
        if len(sections) < 2:
            symbols = []
        else:
            symbols = NmSymbol_C.parse_nm_output(sections[1])
        
        return cls(size_info=size_info, symbols=symbols)

def generate_markdown_report(memory_stats: List[Tuple[str, 'MemStats_C']], output_file: str="build/memory_comparison.md") -> None:
    """
    Generate a markdown file with tables comparing memory statistics.
    
    Args:
        memory_stats: List of tuples (filename, MemStats_C object)
        output_file: Path to the output markdown file
    """
    # Extract filenames for column headers (remove common prefix/suffix for readability)
    filenames = []
    for filename, _ in memory_stats:
        # Extract just the variant part (e.g., "wx86-64-nums-bp-nolut")
        clean_name = filename.replace("memstats_", "").replace(".log", "")
        filenames.append(clean_name)
    
    with open(output_file, 'w') as f:
        # Write header
        f.write("# Memory Usage Comparison\n\n")
        f.write(f"Generated on {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
        
        # Write section 1: Size command output comparison
        f.write("## Memory Section Sizes (Ascending Order of Total Size)\n\n")
        
        # Table header
        f.write("| Configuration | Text | Data | BSS | Total |\n")
        f.write("|--------------|-----:|-----:|----:|------:|\n")
        
        # Table rows (sorted by total size ascending)
        # Pair each filename with its stats and total size
        rows = []
        for i, (_, stats) in enumerate(memory_stats):
            variant = filenames[i]
            size_info = stats.size_info
            rows.append((size_info.dec, variant, stats, f"| {variant} | {size_info.text} | {size_info.data} | {size_info.bss} | {size_info.dec} |\n"))
        # Sort rows by total size (dec)
        rows.sort()
        for _, _, _, row in rows:
            f.write(row)
        
        f.write("\n")
        
        # Write section 2: Symbol comparison
        f.write("## Symbol Sizes (Same Order as Above)\n\n")
        
        # Collect all unique symbol names across all files
        all_symbols = set()
        for _, stats in memory_stats:
            for symbol in stats.symbols:
                all_symbols.add(symbol.name)
        
        # Sort symbols alphabetically
        sorted_symbols = sorted(all_symbols)
        
        # Table header
        header = "| Configuration |"
        for symbol_name in sorted_symbols:
            header += f" {symbol_name} |"
        f.write(header + "\n")
        
        # Separator line
        separator = "|--------------|"
        for _ in sorted_symbols:
            separator += "-----:|"  # Right-align numeric data
        f.write(separator + "\n")
        
        # Table rows - variants, in the same order as Memory Section Sizes table
        for _, variant, stats, _ in rows:
            row = f"| {variant} |"
            # Create a lookup for quick symbol access
            symbol_dict = {symbol.name: symbol.size for symbol in stats.symbols}
            # Add each symbol's size (or - if not present)
            for symbol_name in sorted_symbols:
                if symbol_name in symbol_dict:
                    row += f" {symbol_dict[symbol_name]} |"
                else:
                    row += " - |"
            f.write(row + "\n")

def main():
    """Main entry point for the script."""
    # Default path
    memstats_path = "build/memstats"
    
    # Allow specifying a different path via command line
    if len(sys.argv) > 1:
        memstats_path = sys.argv[1]
    
    # Read all files
    file_contents = read_memstat_files(memstats_path)
    
    if not file_contents:
        print(f"No files were read from {memstats_path}")
        return

    print(f"Successfully read {len(file_contents)} files from {memstats_path}")

    # Parse each file and extract memory stats
    memory_stats = []
    for filename, content in file_contents:
        try:
            stats = MemStats_C.from_log_file(content)
            memory_stats.append((filename, stats))
            print(f"Processed {filename}")
        except Exception as e:
            print(f"Error processing {filename}: {e}")
    
    # Generate markdown report
    output_file = "build/memory_comparison.md"
    generate_markdown_report(memory_stats, output_file)
    print(f"\nMarkdown report generated: {output_file}")

if __name__ == "__main__":
    main()
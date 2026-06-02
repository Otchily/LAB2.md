from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

ROOT = Path('/home/user/minipascal-compiler')
ART = ROOT / 'artifacts'
ART.mkdir(parents=True, exist_ok=True)

sections = [
    ('VERSOES DO AMBIENTE', ART / 'toolchain_versions.txt'),
    ('FACTOR 84', ART / 'factor_output.txt'),
    ('ISPRIME 97', ART / 'isprime_output.txt'),
    ('ISPRIME 91', ART / 'isprime_output_91.txt'),
    ('FIBONACCI 10', ART / 'fibonacci_output.txt'),
    ('PIDIGITS 6', ART / 'pidigits_output.txt'),
]

lines = []
for title, path in sections:
    lines.append('=' * 78)
    lines.append(title)
    lines.append('=' * 78)
    if path.exists():
        lines.extend(path.read_text(encoding='utf-8', errors='ignore').splitlines())
    else:
        lines.append('[arquivo nao encontrado]')
    lines.append('')

text = '\n'.join(lines)
font = ImageFont.load_default()
margin = 24
line_height = 16
max_line = max(len(line) for line in lines) if lines else 40
width = max(1200, margin * 2 + max_line * 8)
height = margin * 2 + line_height * (len(lines) + 2)

img = Image.new('RGB', (width, height), (15, 23, 42))
draw = ImageDraw.Draw(img)
draw.text((margin, margin), text, fill=(230, 240, 255), font=font, spacing=4)
img.save(ART / 'execution_evidence.png')
print(str(ART / 'execution_evidence.png'))

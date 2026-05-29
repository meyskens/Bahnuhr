const sharp = require('sharp');
const fs = require('fs');
const path = require('path');

// Read the DB face PNG file
const inputPath = path.join(__dirname, '..', 'db-face.png');
const outputDir = path.join(__dirname, '..', 'resources', 'images');

// Platform screen sizes from hardware information:
// - Aplite: 144x168, BW, Rectangle
// - Basalt: 144x168, Color, Rectangle
// - Chalk: 180x180, Color, Round
// - Diorite: 144x168, BW, Rectangle
// - Emery: 200x228, Color, Rectangle
// - Flint: 200x228, Color, Round
// - Gabbro: 260x260, Color, Round
const sizes = [
  // Aplite: 144x168, BW
  { name: 'round-aplite', width: 144, height: 168, fit: 'contain' },
  // Basalt: 144x168, Color
  { name: 'round-color', width: 144, height: 168, fit: 'contain' },
  // Chalk: 180x180, Round, Color
  { name: 'round-chalk', width: 180, height: 180, fit: 'contain' },
  // Diorite: 144x168, BW
  { name: 'round-diorite', width: 144, height: 168, fit: 'contain' },
  // Emery: 200x228, Color
  { name: 'round-emery', width: 200, height: 228, fit: 'contain' },
  // Flint: 200x228, Color, Round
  { name: 'round-flint', width: 200, height: 228, fit: 'contain' },
  // Gabbro: 260x260, Color, Round
  { name: 'round-gabbro', width: 260, height: 260, fit: 'contain' },
];

async function convert() {
  // Ensure output directory exists
  if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
  }

  // Process db-face.png
  if (!fs.existsSync(inputPath)) {
    console.error(`Error: ${inputPath} not found!`);
    process.exit(1);
  }

  const imageBuffer = fs.readFileSync(inputPath);

  for (const size of sizes) {
    const outputPath = path.join(outputDir, `db-face-${size.name}.png`);
    await sharp(imageBuffer)
      .resize(size.width, size.height, { fit: size.fit, background: { r: 255, g: 255, b: 255, alpha: 0 } })
      .png()
      .toFile(outputPath);
    console.log(`Created db-face-${size.name}.png`);
  }

  // Process db-face-logo.png
  const logoInputPath = path.join(__dirname, '..', 'db-face-logo.png');
  if (!fs.existsSync(logoInputPath)) {
    console.error(`Error: ${logoInputPath} not found!`);
    process.exit(1);
  }

  const logoBuffer = fs.readFileSync(logoInputPath);

  for (const size of sizes) {
    const outputPath = path.join(outputDir, `db-face-logo-${size.name}.png`);
    await sharp(logoBuffer)
      .resize(size.width, size.height, { fit: size.fit, background: { r: 255, g: 255, b: 255, alpha: 0 } })
      .png()
      .toFile(outputPath);
    console.log(`Created db-face-logo-${size.name}.png`);
  }

  console.log('Conversion complete!');
}

convert().catch(console.error);
